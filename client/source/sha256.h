#pragma once
#include <stdint.h>
#include <stddef.h>

void sha256(const unsigned char* data, size_t len, unsigned char* out);
void sha256_file(const char* path, unsigned char* out);
void sha256_hex(const unsigned char* hash, char* outHex);
