CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread
LDFLAGS = -lcrypto -lssl
LDTESTFLAGS = -lgtest -lgtest_main

SRC = src
BIN = bin
TESTS = tests
INCLUDE = include

block_test:
	$(CXX) $(CXXFLAGS) -I${INCLUDE} $(SRC)/Block.cpp $(SRC)/utils.cpp $(TESTS)/test_block.cpp $(LDFLAGS) $(LDTESTFLAGS) -o $(BIN)/tests/test_block

test: block_test
	@echo "Running tests..."
	@for test in $(BIN)/tests/*; do \
		echo "Running $$test..."; \
		$$test; \
	done

.PHONY:
	block_test && ./bin/tests/test_block