#include "downloader.h"
#include <xtl.h>
#include <stdio.h>
#include <string.h>

bool Downloader::Download(const char* url, const char* destPath, ProgressFn onProgress, void* userdata) {
    if (onProgress) onProgress(0, userdata);
    // TODO: real XDK HTTP streaming download
    return false;
}

bool Downloader::Sha256(const char* path, char* outHex) {
    memset(outHex, '0', 64);
    outHex[64] = 0;
    return true;
}
