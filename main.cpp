#include <iostream>

#include "Block.hpp"
#include "utils.hpp"

using namespace std;

int main()
{
	// Create Genesis Block
	Block genesis;
	// genesis.mine();
	cout << "Genesis Block:\n"
		 << genesis.info() << endl;

	cout << endl;

	// Create a new block referencing the Genesis Block
	Block block1(genesis, "Transaction Data 1");
	block1.mine();
	cout << "Block 1:\n"
		 << block1.info() << endl;

	cout << endl;

	// Create another block referencing Block 1
	Block block2(block1, "Transaction Data 2");
	block2.mine();
	cout << "Block 2:\n"
		 << block2.info() << endl;

	cout << block2.getHash().data() << endl;

	return 0;
}