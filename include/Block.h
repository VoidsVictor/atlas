#ifndef BLOCK_H
#define BLOCK_H

#include <ctime>
#include <string>

class Block
{
	private:
		// Identifiers of the block
		int index;
		time_t timestamp;

		// Data part of the block
		std::string data;
		Block* PrevBlock;

		// Cryptographic part of the block
		int nonce;
		std::string merkle_root;
		std::string hash;

	public:
		Block();
		Block(Block& PrevBlock, std::string data);
		std::string info();
};

#endif