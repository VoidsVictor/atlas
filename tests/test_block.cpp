#include "BlockChain/Block.hpp"
#include "utils.hpp"
#include <cstring> // for memcmp
#include <gtest/gtest.h>

// Test Genesis Block Initialization
TEST(BlockTest, GenesisBlockInitialization)
{
	Block genesisBlock;

	EXPECT_EQ(genesisBlock.info().empty(), false);	   // Check if info() returns something
	EXPECT_EQ(genesisBlock.info().find("Block 0"), 0); // Ensure it's the first block
}

// Test Standard Block Creation
TEST(BlockTest, StandardBlockCreation)
{
	Block genesisBlock;
	Block newBlock(genesisBlock, "Sample Data");

	EXPECT_NE(genesisBlock.info(), newBlock.info());						   // Ensure different blocks
	EXPECT_EQ(newBlock.info().find("Sample Data") != std::string::npos, true); // Data should be present
}

// Test Standard Block Indexing
TEST(BlockTest, BlockIndexing)
{
	Block genesisBlock;
	Block block1(genesisBlock, "Data 1");
	Block block2(block1, "Data 2");

	EXPECT_EQ(block1.info().find("Block 1") != std::string::npos, true); // Block 1 should have index 1
	EXPECT_EQ(block2.info().find("Block 2") != std::string::npos, true); // Block 2 should have index 2
}

// Test Mining Updates Timestamp
TEST(BlockTest, MiningUpdatesTimestamp)
{
	Block genesisBlock;
	Block newBlock(genesisBlock, "Sample Data");

	time_t oldTimestamp = newBlock.getTimestamp();
	newBlock.mine();

	EXPECT_NE(newBlock.getTimestamp(), oldTimestamp); // Timestamp should change after mining
}

// Main Function to Run Tests
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
