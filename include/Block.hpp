#ifndef BLOCK_H
#define BLOCK_H

#include <ctime>
#include <map>
#include <openssl/sha.h>
#include <string>

class Block
{
	private:
		// Identifiers of the block
		int index;
		time_t timestamp;

		// Data part of the block
		// std::map<std::string, std::string> data;
		std::string data;
		Block* PrevBlock;

		// Cryptographic part of the block
		// TODO Implement merkle root
		std::string merkle_root;
		unsigned char hash[SHA256_DIGEST_LENGTH];

	public:
		// Genesis Block
		Block();

		// Standard Block
		Block(Block& PrevBlock, std::string data);

		// Block information
		std::string info();

		// Mine Block
		// TODO Should contain a smart contract executer object to execute smart contracts as input
		void mine();
};

#endif