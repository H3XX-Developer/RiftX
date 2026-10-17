#include "sha256.h"
#include <xtl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Public domain SHA-256 based on LibTomCrypt / Wei Dai implementations.
// Adapted for Xbox 360 (no <stdint.h> conflicts handled via xtl.h).

static const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SIG0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define SIG1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define sig0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ ((x) >> 3))
#define sig1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ ((x) >> 10))

static void sha256_transform(uint32_t state[8], const uint8_t block[64]) {
    uint32_t W[64];
    for (int i = 0; i < 16; i++) {
        W[i] = ((uint32_t)block[i*4] << 24) | ((uint32_t)block[i*4+1] << 16) |
               ((uint32_t)block[i*4+2] << 8) | ((uint32_t)block[i*4+3]);
    }
    for (int i = 16; i < 64; i++) {
        W[i] = sig1(W[i-2]) + W[i-7] + sig0(W[i-15]) + W[i-16];
    }

    uint32_t a = state[0], b = state[1], c = state[2], d = state[3];
    uint32_t e = state[4], f = state[5], g = state[6], h = state[7];

    for (int i = 0; i < 64; i++) {
        uint32_t t1 = h + SIG1(e) + CH(e, f, g) + K[i] + W[i];
        uint32_t t2 = SIG0(a) + MAJ(a, b, c);
        h = g; g = f; f = e; e = d + t1;
        d = c; c = b; b = a; a = t1 + t2;
    }

    state[0] += a; state[1] += b; state[2] += c; state[3] += d;
    state[4] += e; state[5] += f; state[6] += g; state[7] += h;
}

void sha256(const unsigned char* data, size_t len, unsigned char* out) {
    uint32_t state[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    size_t i = 0;
    for (; i + 64 <= len; i += 64) sha256_transform(state, data + i);

    uint8_t final[128];
    size_t rem = len - i;
    memcpy(final, data + i, rem);
    final[rem] = 0x80;
    if (rem < 56) {
        memset(final + rem + 1, 0, 56 - rem - 1);
    } else {
        memset(final + rem + 1, 0, 120 - rem - 1);
        sha256_transform(state, final);
        memset(final, 0, 56);
    }
    uint64_t bitlen = (uint64_t)len * 8;
    for (int j = 0; j < 8; j++) final[56 + j] = (uint8_t)(bitlen >> (56 - j*8));
    sha256_transform(state, final);

    for (int j = 0; j < 8; j++) {
        out[j*4]   = (state[j] >> 24) & 0xff;
        out[j*4+1] = (state[j] >> 16) & 0xff;
        out[j*4+2] = (state[j] >> 8) & 0xff;
        out[j*4+3] = state[j] & 0xff;
    }
}

void sha256_file(const char* path, unsigned char* out) {
    FILE* f = fopen(path, "rb");
    if (!f) { memset(out, 0, 32); return; }

    uint32_t state[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    uint8_t buf[64];
    size_t n;
    uint64_t total = 0;
    while ((n = fread(buf, 1, 64, f)) == 64) {
        sha256_transform(state, buf);
        total += 64;
    }
    total += n;

    uint8_t final[128];
    memcpy(final, buf, n);
    final[n] = 0x80;
    if (n < 56) memset(final + n + 1, 0, 56 - n - 1);
    else { memset(final + n + 1, 0, 120 - n - 1); sha256_transform(state, final); memset(final, 0, 56); }
    uint64_t bitlen = total * 8;
    for (int j = 0; j < 8; j++) final[56 + j] = (uint8_t)(bitlen >> (56 - j*8));
    sha256_transform(state, final);

    for (int j = 0; j < 8; j++) {
        out[j*4]   = (state[j] >> 24) & 0xff;
        out[j*4+1] = (state[j] >> 16) & 0xff;
        out[j*4+2] = (state[j] >> 8) & 0xff;
        out[j*4+3] = state[j] & 0xff;
    }
    fclose(f);
}

void sha256_hex(const unsigned char* hash, char* outHex) {
    static const char hex[] = "0123456789abcdef";
    for (int i = 0; i < 32; i++) {
        outHex[i*2]   = hex[hash[i] >> 4];
        outHex[i*2+1] = hex[hash[i] & 0xf];
    }
    outHex[64] = 0;
}
