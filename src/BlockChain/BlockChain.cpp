#include <iostream>

#include "BlockChain/Block.hpp"
#include "BlockChain/BlockChain.hpp"
#include "utils.hpp"

using namespace std;

BlockChain::BlockChain()
{
	Block genesis;
	chain.push_back(genesis);
}

bool BlockChain::isNextBlockValid(Block block) // Pass by reference
{
	Block prevBlock = getLastBlock();

	if (block.getIndex() != prevBlock.getIndex() + 1)
	{
		// cout << "Block index is not valid" << endl;
		return false;
	}

	if (hashToHexString(block.getPrevBlockHash()) != hashToHexString(prevBlock.getHash()))
	{
		// cout << "Block hash is not valid" << endl;
		return false;
	}

	return true;
}

void BlockChain::addBlock(Block block)
{
	if (!isNextBlockValid(block))
	{
		throw std::runtime_error("Invalid block");
	}

	block.mine();
	chain.push_back(block);
}

Block BlockChain::getLastBlock()
{
	return chain.back();
}

std::vector<Block> BlockChain::getChain()
{
	return chain;
}
