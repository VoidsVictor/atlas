#include "Block.hpp"
#include <gtest/gtest.h>

// Sample test case for Genesis Block
TEST(BlockTest, GenesisBlock)
{
	Block genesisBlock;
	EXPECT_EQ(genesisBlock.info().empty(), false); // Check if info() returns something
}

// Sample test case for Standard Block
TEST(BlockTest, StandardBlock)
{
	Block genesisBlock;
	Block newBlock(genesisBlock, "Sample Data");

	EXPECT_NE(genesisBlock.info(), newBlock.info()); // Ensure different blocks
}

// Add more tests as needed

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
