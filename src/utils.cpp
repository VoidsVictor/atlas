#include <chrono>
#include <cstring>
#include <iomanip>
#include <ios>
#include <openssl/sha.h>

#include "utils.h"

// Returns the current epoch time
time_t epochTimeStamp()
{
	auto now = std::chrono::system_clock::now();
	return std::chrono::system_clock::to_time_t(now);
}

// Hashes a string using SHA256 and outputs the raw hash
void computeSHA256(const std::string& data, unsigned char* hash)
{
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, data.c_str(), data.size());
	SHA256_Final(hash, &sha256); // Writes directly to 'hash'
}

// Converts a raw SHA256 hash (unsigned char array) to a hex string
std::string hashToHexString(const unsigned char* hash, size_t length)
{
	std::ostringstream oss;
	oss << std::hex << std::setfill('0'); // Set hex formatting and fill with '0' for uniformity

	for (size_t i = 0; i < length; ++i)
	{
		oss << std::setw(2) << static_cast<int>(hash[i]); // Convert each byte to a two-character hex representation
	}

	return oss.str();
}

// Checks whether a hash if valid or not
bool isHashUnitialised(const unsigned char hash[SHA256_DIGEST_LENGTH])
{
	static const unsigned char empty[SHA256_DIGEST_LENGTH] = {0};
	return memcmp(hash, empty, SHA224_DIGEST_LENGTH);
}