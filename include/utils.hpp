#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <chrono>
#include <openssl/sha.h>
#include <string>

// Returns the current epoch time.
time_t epochTimeStamp();

// Hashes a string using SHA256 and outputs the raw hash.
void computeSHA256(const std::string& data, std::array<unsigned char, SHA256_DIGEST_LENGTH>* hash);

// Converts a raw SHA256 hash to a hex string representation.
std::string hashToHexString(const std::array<unsigned char, SHA256_DIGEST_LENGTH>& hash, size_t length = SHA256_DIGEST_LENGTH);

// Checks whether a hash is uninitialized (i.e. all zeros).
bool isHashUnitialised(const unsigned char hash[SHA256_DIGEST_LENGTH]);

// Calculate the merkle root for the data
std::array<unsigned char, SHA256_DIGEST_LENGTH> merkleRoot(const std::string& data);

#endif // UTILS_H
