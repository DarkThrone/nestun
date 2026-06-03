CXX      := clang++
CXXFLAGS := -std=c++23 -Wall -Wextra -Wpedantic -g
INCLUDES := -I include -I external

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

.PHONY: all test bear clean setup help

all: $(TARGET) ## Build the entire project

$(TARGET): $(SRC_OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

test: $(TEST_BIN) ## Test the project
	@$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS) $(LIB_OBJS) | $(TEST_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_DIR)/%.o: tests/%.cpp | $(TEST_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR) $(OBJ_DIR) $(TEST_DIR):
	mkdir -p $@

# Regenerate compile_commands.json for clangd
bear: clean ## Generate compile_commands.json for LSP autompletion
	bear -- $(MAKE) all test

clean: ## Clean all the build files
	rm -rf $(BUILD_DIR)

# Download doctest header
setup: external/doctest.h ## Download and setup doctest.h

external/doctest.h:
	mkdir -p external
	curl -fL $(DOCTEST_URL) -o $@

help: ## List available make targets
	@grep -E '^[a-zA-Z0-9_.-]+:.*## ' $(firstword $(MAKEFILE_LIST)) | \
		sort | \
		awk 'BEGIN { FS = ":.*## " } { printf "%-20s %s\n", $$1, $$2 }'

