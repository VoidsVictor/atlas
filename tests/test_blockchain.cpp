#include <gtest/gtest.h>

#include "BlockChain/BlockChain.hpp"

// Test Blockchain Initialization
TEST(BlockChainTest, GenesisBlockExists)
{
	BlockChain blockchain;
	std::vector<Block> chain = blockchain.getChain();

	// Ensure there is exactly one block (Genesis block) in the chain
	ASSERT_EQ(chain.size(), 1);

	// Check if the first block is the Genesis block
	EXPECT_EQ(chain[0].getIndex(), 0);
}

// Test adding a block
TEST(BlockChainTest, AddingBlock)
{
	BlockChain blockchain;
	Block prevBlock = blockchain.getLastBlock();
	Block newBlock(prevBlock, "Transaction Data 1");
	blockchain.addBlock(newBlock);

	std::vector<Block> chain = blockchain.getChain();

	// Ensure there is two blocks (Genesis block + new block)
	ASSERT_EQ(chain.size(), 2);

	// Check the second block
	EXPECT_EQ(chain.back().getIndex(), 1);
}
