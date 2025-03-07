#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <chrono>
#include <openssl/sha.h>
#include <string>

time_t epochTimeStamp();
void hash(std::string hash);
void computeSHA256(const std::string& data, std::array<unsigned char, SHA256_DIGEST_LENGTH>* hash);
std::string hashToHexString(std::array<unsigned char, SHA256_DIGEST_LENGTH> hash, size_t length = SHA256_DIGEST_LENGTH);
bool isHashUnitialised(const unsigned char hash[SHA256_DIGEST_LENGTH]);

#endif