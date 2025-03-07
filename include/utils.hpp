#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <openssl/sha.h>
#include <string>

time_t epochTimeStamp();
void hash(std::string hash);
void computeSHA256(const std::string& data, unsigned char* hash);
std::string hashToHexString(const unsigned char* hash, size_t length = SHA256_DIGEST_LENGTH);
bool isHashUnitialised(const unsigned char hash[SHA256_DIGEST_LENGTH]);

#endif