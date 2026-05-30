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

.PHONY: all test bear clean setup

all: $(TARGET)

$(TARGET): $(SRC_OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

test: $(TEST_BIN)
	@$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS) $(LIB_OBJS) | $(TEST_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_DIR)/%.o: tests/%.cpp | $(TEST_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR) $(OBJ_DIR) $(TEST_DIR):
	mkdir -p $@

# Regenerate compile_commands.json for clangd
bear: clean
	bear -- $(MAKE) all test

clean:
	rm -rf $(BUILD_DIR)

# Download doctest header
setup: external/doctest.h

external/doctest.h:
	mkdir -p external
	curl -fL $(DOCTEST_URL) -o $@
