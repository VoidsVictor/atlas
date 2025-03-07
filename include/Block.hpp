#ifndef BLOCK_H
#define BLOCK_H

#include <array>
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
		std::array<unsigned char, SHA256_DIGEST_LENGTH> merkle_root;
		std::array<unsigned char, SHA256_DIGEST_LENGTH> hash;

	public:
		// Genesis Block
		Block();

		// Standard Block
		Block(Block& PrevBlock, std::string data);

		// Block information
		std::string info();

		// Getters
		int getIndex();
		time_t getTimestamp();
		std::string getData();
		std::array<unsigned char, SHA256_DIGEST_LENGTH> getHash();

		// Mine Block
		// TODO Should contain a smart contract executer object as input to execute smart contracts
		void mine();
};

#endif