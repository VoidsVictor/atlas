#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <vector>

#include "Block.hpp"

class BlockChain
{
	private:
		std::vector<Block> chain;

	public:
		BlockChain();
		void addBlock(Block block);
		Block getLastBlock();
		std::vector<Block> getChain();
		bool isNextBlockValid(Block block);
};

#endif