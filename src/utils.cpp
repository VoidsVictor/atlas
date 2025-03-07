#include <chrono>
#include <cstring>
#include <iomanip>
#include <ios>
#include <openssl/evp.h>
#include <stdexcept>

#include "utils.hpp"

// Returns the current epoch time
time_t epochTimeStamp()
{
	auto now = std::chrono::system_clock::now();
	return std::chrono::system_clock::to_time_t(now);
}

// Hashes a string using SHA256 and outputs the raw hash
void computeSHA256(const std::string& data, unsigned char* hash)
{
	EVP_MD_CTX* context = EVP_MD_CTX_new();
	if (context == nullptr)
		throw std::runtime_error("Failed to create EVP_MD_CTX");

	if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1)
	{
		EVP_MD_CTX_free(context);
		throw std::runtime_error("EVP_DigestInit_ex failed");
	}

	if (EVP_DigestUpdate(context, data.c_str(), data.size()) != 1)
	{
		EVP_MD_CTX_free(context);
		throw std::runtime_error("EVP_DigestUpdate failed");
	}

	unsigned int lengthOfHash = 0;
	if (EVP_DigestFinal_ex(context, hash, &lengthOfHash) != 1)
	{
		EVP_MD_CTX_free(context);
		throw std::runtime_error("EVP_DigestFinal_ex failed");
	}

	EVP_MD_CTX_free(context);
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