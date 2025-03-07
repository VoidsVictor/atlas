#include <array>
#include <sstream>

#include "Block.hpp"
#include "utils.hpp"

Block::Block()
	: index{0},
	  timestamp{},
	  data{""},
	  PrevBlock{nullptr},
	  merkle_root{""},
	  hash{} {}

Block::Block(Block& PrevBlock, std::string data)
	: index{++PrevBlock.index},
	  timestamp{},
	  data{data},
	  PrevBlock{&PrevBlock},
	  merkle_root{""},
	  hash{} {}

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
	std::array<unsigned char, SHA256_DIGEST_LENGTH> hashArray;
	std::copy(std::begin(hash), std::end(hash), hashArray.begin());
	return hashArray;
}

std::string Block::info()
{
	std::ostringstream oss;
	oss << "Block " << index << "\n"
		<< "Epoch Timestamp: " << timestamp << "\n"
		<< "Block Hash: " << hashToHexString(hash) << "\n"
		<< "Previous Block Hash: " << (PrevBlock ? hashToHexString(PrevBlock->hash) : "None") << "\n"
		<< "Merkle Root: " << merkle_root << "\n"
		<< "Status: " << (!isHashUnitialised(hash.data()) ? "Not Mined" : "Mined") << "\n"
		<< "Data: " << "\n"
		<< data << "\n";
	return oss.str();
}

void Block::mine()
{
	// Initialising content
	timestamp = epochTimeStamp();

	// TODO Calculate Merkle root

	// Calculating hash
	std::ostringstream oss;
	oss << index << timestamp << PrevBlock->hash.data() << data << merkle_root;

	std::string block = oss.str();
	computeSHA256(block, &hash);
}