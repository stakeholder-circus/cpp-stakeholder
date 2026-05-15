CXX ?= c++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Werror -O2
BUILD_DIR := build
BIN := $(BUILD_DIR)/cpp-stakeholder
SRC := src/main.cpp

.PHONY: all compiler-proof test clean

all: $(BIN)

$(BIN): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN)

compiler-proof:
	$(CXX) --version

test: $(BIN)
	bash tests/test_cli.sh

clean:
	rm -rf $(BUILD_DIR)
