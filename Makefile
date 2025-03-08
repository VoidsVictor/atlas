CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread
LDFLAGS = -lcrypto -lssl
LDTESTFLAGS = -lgtest -lgtest_main

SRC = src
BIN = bin
TESTS = tests
INCLUDE = include
BIN_TESTS = $(BIN)/tests

# Ensure bin and bin/tests directories exist before compiling
$(BIN) $(BIN_TESTS):
	mkdir -p $(BIN) $(BIN_TESTS)

# Build test executable
$(BIN_TESTS)/test_block: $(SRC)/Block.cpp $(SRC)/utils.cpp $(TESTS)/test_block.cpp | $(BIN) $(BIN_TESTS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) $^ $(LDFLAGS) $(LDTESTFLAGS) -o $@

$(BIN_TESTS)/test_blockchain: $(SRC)/Block.cpp $(SRC)/BlockChain.cpp $(SRC)/utils.cpp $(TESTS)/test_blockchain.cpp | $(BIN) $(BIN_TESTS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) $^ $(LDFLAGS) $(LDTESTFLAGS) -o $@

# Run tests
test: $(BIN_TESTS)/test_block $(BIN_TESTS)/test_blockchain
	@echo "Running tests..."
	@for test in $(BIN_TESTS)/*; do \
		echo "Running $$test..."; \
		$$test; \
	done

# Build everything
all: $(BIN_TESTS)/test_block

# Clean build artifacts
clean:
	rm -rf $(BIN)

.PHONY: all test clean
