#include "Block.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	// Create Genesis Block (with empty or non-JSON data)
	Block genesis;
	cout << "Genesis Block:\n"
		 << genesis.info() << endl;
	cout << endl;

	// Create Block 1 using plain text (non-JSON) data
	Block block1(genesis, "Transaction Data 1");
	block1.mine();
	cout << "Block 1 (Non-JSON data):\n"
		 << block1.info() << endl;
	cout << endl;

	// Create Block 2 using plain text (non-JSON) data
	Block block2(block1, "Transaction Data 2");
	block2.mine();
	cout << "Block 2 (Non-JSON data):\n"
		 << block2.info() << endl;
	cout << endl;

	// Create Block 3 using valid JSON object data
	string jsonData = R"({"sender": "Alice", "recipient": "Bob", "amount": 100})";
	Block block3(block2, jsonData);
	block3.mine();
	cout << "Block 3 (JSON Object data):\n"
		 << block3.info() << endl;
	cout << endl;

	// Create Block 4 using valid JSON array data
	string jsonArrayData = R"(["apple", "banana", "cherry"])";
	Block block4(block3, jsonArrayData);
	block4.mine();
	cout << "Block 4 (JSON Array data):\n"
		 << block4.info() << endl;
	cout << endl;

	// Print the final block's hash in hex format
	cout << "Block 4 Hash (raw hex): " << hashToHexString(block4.getHash()) << endl;

	return 0;
}
