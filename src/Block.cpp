#include <sstream>

#include "Block.h"
#include "utils.h"

Block::Block()
	: PrevBlock{nullptr},
	  index{0},
	  timestamp{epochTimeStamp()},
	  nonce{0},
	  data{""},
	  merkle_root{""},
	  hash{""} {}

Block::Block(Block& PrevBlock, std::string data)
	: PrevBlock{&PrevBlock},
	  index{++PrevBlock.index},
	  timestamp{epochTimeStamp()},
	  nonce{0},
	  data{data},
	  merkle_root{""},
	  hash{""} {}

std::string Block::info()
{
	std::ostringstream oss;
	oss << "Block " << index << "\n"
		<< "Epoch Timestamp: " << timestamp << "\n"
		<< "Block Hash: " << hash << "\n"
		<< "Previous Block Hash: " << (PrevBlock ? PrevBlock->hash : "None") << "\n"
		<< "Merkle Root: " << merkle_root << "\n"
		<< "Status: " << (hash == "" ? "Not Mined" : "Mined");
	return oss.str();
}