#include <array>
#include <sstream>
#include <string>

#include "BlockChain/Block.hpp"
#include "utils.hpp"

// Block initialization function
Block::Block()
	: index(0),
	  timestamp(0),
	  data(""),
	  PrevBlock(nullptr),
	  merkle_root{},
	  hash{} {}

Block::Block(Block& previousBlock, std::string data)
	: index(previousBlock.index + 1), // Use previous block's index + 1
	  timestamp(0),
	  data(data),
	  PrevBlock(&previousBlock),
	  merkle_root{},
	  hash{}
{
}

// Getter functions
int Block::getIndex()
{
	return index;
}

time_t Block::getTimestamp()
{
	return timestamp;
}

std::string Block::getData()
{
	return data;
}

std::array<unsigned char, SHA256_DIGEST_LENGTH> Block::getHash()
{
	return hash;
}
std::array<unsigned char, SHA256_DIGEST_LENGTH> Block::getMerkleRoot()
{
	return merkle_root;
}

std::array<unsigned char, SHA256_DIGEST_LENGTH> Block::getPrevBlockHash()
{
	if (PrevBlock)
		return PrevBlock->hash;
	else
	{
		std::array<unsigned char, SHA256_DIGEST_LENGTH> emptyHash = {0};
		return emptyHash;
	}
}

// Function to output block information
std::string Block::info()
{
	std::ostringstream oss;
	oss << "Block " << index << "\n"
		<< "Epoch Timestamp: " << timestamp << "\n"
		<< "Block Hash: " << hashToHexString(hash) << "\n"
		<< "Previous Block Hash: "
		<< (PrevBlock ? hashToHexString(PrevBlock->hash) : "None") << "\n"
		<< "Merkle Root: " << hashToHexString(merkle_root) << "\n"
		<< "Status: "
		<< (isHashUnitialised(hash.data()) ? "Not Mined" : "Mined") << "\n"
		<< "Data: \n"
		<< data << "\n";
	return oss.str();
}

// Function to mine block
void Block::mine()
{
	// Set the block's timestamp
	timestamp = epochTimeStamp();

	// Calculate the Merkle Root from the block's data.
	// Convert the raw hash to a hex string for storage.
	merkle_root = merkleRoot(data);

	// Build a payload string for hashing.
	std::ostringstream oss;
	oss << index << timestamp;
	if (PrevBlock)
		oss << hashToHexString(PrevBlock->hash);
	else
		oss << "0"; // Use a default value if no previous block
	oss << data << hashToHexString(merkle_root);

	std::string blockPayload = oss.str();
	computeSHA256(blockPayload, &hash);
}
