CXX      := clang++
CXXFLAGS := -std=c++23 -Wall -Wextra -Wpedantic -g
INCLUDES := -I include -I external -I external/raylib/src

BUILD_DIR := build
OBJ_DIR   := $(BUILD_DIR)/obj
TEST_DIR  := $(BUILD_DIR)/test

TARGET   := $(BUILD_DIR)/nestun
TEST_BIN := $(TEST_DIR)/tests

SRC_SRCS  := $(wildcard src/*.cpp)
SRC_OBJS  := $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRC_SRCS))
LIB_OBJS  := $(filter-out $(OBJ_DIR)/main.o,$(SRC_OBJS))

TEST_SRCS := $(wildcard tests/*.cpp)
TEST_OBJS := $(patsubst tests/%.cpp,$(TEST_DIR)/%.o,$(TEST_SRCS))

DOCTEST_VERSION := 2.4.11
DOCTEST_URL := https://github.com/doctest/doctest/releases/download/v$(DOCTEST_VERSION)/doctest.h

# ── Raylib ──────────────────────────────────────────────
RAYLIB_DIR := external/raylib/src
RAYLIB_LIB := $(RAYLIB_DIR)/libraylib.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    RAYLIB_LDFLAGS := $(RAYLIB_LIB) \
        -framework IOKit -framework Cocoa -framework OpenGL
else
    RAYLIB_LDFLAGS := $(RAYLIB_LIB) \
        -lGL -lm -lpthread -ldl -lrt -lX11
endif
# ────────────────────────────────────────────────────────

.PHONY: all test bear clean setup help raylib

all: $(TARGET) ## Build the entire project

$(TARGET): $(SRC_OBJS) $(RAYLIB_LIB) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_OBJS) $(RAYLIB_LDFLAGS) -o $@

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# ── Raylib build ────────────────────────────────────────
$(RAYLIB_LIB):
	$(MAKE) -C $(RAYLIB_DIR) CC=clang PLATFORM=PLATFORM_DESKTOP

raylib: ## Rebuild raylib from source
	$(MAKE) -C $(RAYLIB_DIR) clean
	$(MAKE) -C $(RAYLIB_DIR) CC=clang PLATFORM=PLATFORM_DESKTOP
# ────────────────────────────────────────────────────────

test: $(TEST_BIN) ## Test the project
	@$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS) $(LIB_OBJS) | $(TEST_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_DIR)/%.o: tests/%.cpp | $(TEST_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR) $(OBJ_DIR) $(TEST_DIR):
	mkdir -p $@

bear: clean ## Generate compile_commands.json for LSP autocompletion
	bear -- $(MAKE) all test

clean: ## Clean all the build files
	rm -rf $(BUILD_DIR)

clean-all: clean ## Clean build files + raylib
	$(MAKE) -C $(RAYLIB_DIR) clean

setup: external/doctest.h ## Download and setup doctest.h

external/doctest.h:
	mkdir -p external
	curl -fL $(DOCTEST_URL) -o $@

help: ## List available make targets
	@grep -E '^[a-zA-Z0-9_.-]+:.*## ' $(firstword $(MAKEFILE_LIST)) | \
		sort | \
		awk 'BEGIN { FS = ":.*## " } { printf "%-20s %s\n", $$1, $$2 }'
