#include "utils.hpp"
#include "json.hpp"
#include <algorithm>
#include <array>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <ios>
#include <openssl/evp.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace nlohmann;
using namespace std;

// Returns the current epoch time
time_t epochTimeStamp()
{
	auto now = chrono::system_clock::now();
	return chrono::system_clock::to_time_t(now);
}

// Hashes a string using SHA256 and outputs the raw hash
void computeSHA256(const string& data, array<unsigned char, SHA256_DIGEST_LENGTH>* hash)
{
	EVP_MD_CTX* context = EVP_MD_CTX_new();
	if (context == nullptr)
		throw runtime_error("Failed to create EVP_MD_CTX");

	if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1)
	{
		EVP_MD_CTX_free(context);
		throw runtime_error("EVP_DigestInit_ex failed");
	}

	if (EVP_DigestUpdate(context, data.c_str(), data.size()) != 1)
	{
		EVP_MD_CTX_free(context);
		throw runtime_error("EVP_DigestUpdate failed");
	}

	unsigned int lengthOfHash = 0;
	if (EVP_DigestFinal_ex(context, hash->data(), &lengthOfHash) != 1)
	{
		EVP_MD_CTX_free(context);
		throw runtime_error("EVP_DigestFinal_ex failed");
	}

	EVP_MD_CTX_free(context);
}

// Converts a raw SHA256 hash (unsigned char array) to a hex string
string hashToHexString(const array<unsigned char, SHA256_DIGEST_LENGTH>& hash, size_t length)
{
	ostringstream oss;
	oss << hex << setfill('0'); // Set hex formatting and fill with '0' for uniformity

	for (size_t i = 0; i < length; ++i)
	{
		oss << setw(2) << static_cast<int>(hash[i]); // Convert each byte to a two-character hex representation
	}

	return oss.str();
}

// Checks whether a hash is uninitialized (all zeros)
bool isHashUnitialised(const unsigned char hash[SHA256_DIGEST_LENGTH])
{
	static const unsigned char empty[SHA256_DIGEST_LENGTH] = {0};
	return memcmp(hash, empty, SHA256_DIGEST_LENGTH) == 0;
}

// Compute Merkle Root from a vector of hashes
array<unsigned char, SHA256_DIGEST_LENGTH> computeMerkleRoot(vector<array<unsigned char, SHA256_DIGEST_LENGTH>> hashes)
{
	if (hashes.empty())
	{
		array<unsigned char, SHA256_DIGEST_LENGTH> emptyHash = {0};
		return emptyHash;
	}

	while (hashes.size() > 1)
	{
		if (hashes.size() % 2 != 0)
			hashes.push_back(hashes.back()); // Duplicate last element if odd

		vector<array<unsigned char, SHA256_DIGEST_LENGTH>> newLevel;

		for (size_t i = 0; i < hashes.size(); i += 2)
		{
			// Concatenate the two hashes
			vector<unsigned char> combinedHash;
			combinedHash.insert(combinedHash.end(), hashes[i].begin(), hashes[i].end());
			combinedHash.insert(combinedHash.end(), hashes[i + 1].begin(), hashes[i + 1].end());

			// Compute the SHA-256 hash of the concatenated result.
			// Use reinterpret_cast to convert the unsigned char* to const char*
			array<unsigned char, SHA256_DIGEST_LENGTH> tempHash;
			computeSHA256(string(reinterpret_cast<const char*>(combinedHash.data()), combinedHash.size()), &tempHash);

			newLevel.push_back(tempHash);
		}

		hashes = newLevel;
	}

	return hashes[0];
}

// Parses a string as a JSON object and calculates the Merkle Root
array<unsigned char, SHA256_DIGEST_LENGTH> merkleRoot(const string& data)
{
	json jsonData = json::parse(data);

	if (jsonData.is_string())
	{
		array<unsigned char, SHA256_DIGEST_LENGTH> hash;
		computeSHA256(jsonData.get<string>(), &hash);
		return hash;
	}

	if (jsonData.is_number() || jsonData.is_boolean() || jsonData.is_null())
	{
		array<unsigned char, SHA256_DIGEST_LENGTH> hash;
		computeSHA256(jsonData.dump(), &hash); // Convert primitive types to string and hash them
		return hash;
	}

	if (jsonData.is_array())
	{
		// Handle empty array case
		if (jsonData.empty())
		{
			array<unsigned char, SHA256_DIGEST_LENGTH> hash = {0};
			return hash;
		}

		vector<array<unsigned char, SHA256_DIGEST_LENGTH>> hashedElements;
		for (size_t i = 0; i < jsonData.size(); ++i)
		{
			// Recursively compute the Merkle Root for each element.
			array<unsigned char, SHA256_DIGEST_LENGTH> elementHash = merkleRoot(jsonData[i].dump());
			// Convert the resulting hash to a hex string for deterministic concatenation
			string hashHex = hashToHexString(elementHash, SHA256_DIGEST_LENGTH);
			string hashPayload = to_string(i) + ":" + hashHex;
			array<unsigned char, SHA256_DIGEST_LENGTH> hash;
			computeSHA256(hashPayload, &hash);
			hashedElements.push_back(hash);
		}
		return computeMerkleRoot(hashedElements);
	}

	if (jsonData.is_object())
	{
		// Handle empty object case
		if (jsonData.empty())
		{
			array<unsigned char, SHA256_DIGEST_LENGTH> hash = {0};
			return hash;
		}

		vector<array<unsigned char, SHA256_DIGEST_LENGTH>> hashedKeyValues;
		vector<string> sortedKeys;

		for (const auto& [key, _] : jsonData.items())
		{
			sortedKeys.push_back(key);
		}

		sort(sortedKeys.begin(), sortedKeys.end()); // Ensure deterministic order

		for (const auto& key : sortedKeys)
		{
			array<unsigned char, SHA256_DIGEST_LENGTH> valueHash = merkleRoot(jsonData[key].dump());
			string hashHex = hashToHexString(valueHash, SHA256_DIGEST_LENGTH);
			string hashPayload = key + ":" + hashHex;
			array<unsigned char, SHA256_DIGEST_LENGTH> hash;
			computeSHA256(hashPayload, &hash);
			hashedKeyValues.push_back(hash);
		}

		return computeMerkleRoot(hashedKeyValues);
	}

	throw runtime_error("Unhandled JSON type encountered!");
}