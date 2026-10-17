#include "downloader.h"
#include "sha256.h"
#include <xtl.h>
#include <stdio.h>
#include <string.h>

bool Downloader::Download(const char* url, const char* destPath, ProgressFn onProgress, void* userdata) {
    if (onProgress) onProgress(0, userdata);
    // TODO: real XDK HTTP streaming download
    // Use XNetHttpRequest / XHttpRequest here when you have the XDK.
    return false;
}

bool Downloader::Sha256(const char* path, char* outHex) {
    unsigned char hash[32];
    sha256_file(path, hash);
    sha256_hex(hash, outHex);
    return true;
}
