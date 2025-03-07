#include "json.hpp"
#include <iostream>
#include <map>
#include <openssl/sha.h>
#include <vector>

using json = nlohmann::json;
using namespace std;

// Function to compute SHA-256 hash
string sha256(const string& data)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256((unsigned char*)data.c_str(), data.size(), hash);

	// Convert hash to hex string
	string hexHash;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		char buf[3];
		sprintf(buf, "%02x", hash[i]);
		hexHash += buf;
	}
	return hexHash;
}

// Function to compute Merkle Root from a list of hashes
string computeMerkleRoot(vector<string> hashes)
{
	if (hashes.empty())
		return "";

	while (hashes.size() > 1)
	{
		if (hashes.size() % 2 != 0)
		{ // If odd, duplicate last hash
			hashes.push_back(hashes.back());
		}

		vector<string> newLevel;
		for (size_t i = 0; i < hashes.size(); i += 2)
		{
			string combined = hashes[i] + hashes[i + 1];
			newLevel.push_back(sha256(combined));
		}
		hashes = newLevel;
	}
	return hashes[0]; // Final Merkle Root
}

// Recursive function to process any JSON structure
string hashJson(const json& jsonData)
{
	if (jsonData.is_string())
	{
		return sha256(jsonData.get<string>());
	}
	else if (jsonData.is_array())
	{
		vector<string> hashedElements;
		for (const auto& element : jsonData)
		{
			hashedElements.push_back(hashJson(element));
		}
		return computeMerkleRoot(hashedElements);
	}
	else if (jsonData.is_object())
	{
		vector<string> hashedKeyValues;
		for (const auto& [key, value] : jsonData.items())
		{
			string combined = key + ":" + hashJson(value);
			hashedKeyValues.push_back(sha256(combined));
		}
		return computeMerkleRoot(hashedKeyValues);
	}
	else
	{
		return sha256(jsonData.dump()); // Handles numbers, booleans, null, etc.
	}
}

int main()
{
	string jsonString = R"({
        "transactions": {
            "tx1": "data1",
            "tx2": ["data2", "data3"],
            "tx3": {
                "nested1": "value1",
                "nested2": ["value2", "value3"]
            },
            "tx4": "data4"
        }
    })";

	json jsonData = json::parse(jsonString);

	string merkleRoot = hashJson(jsonData);
	cout << "Merkle Root: " << merkleRoot << endl;

	return 0;
}
