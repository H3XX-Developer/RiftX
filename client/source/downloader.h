#pragma once

typedef void (*ProgressFn)(int percent, void* userdata);

namespace Downloader {
    bool Download(const char* url, const char* destPath, ProgressFn onProgress, void* userdata);
    bool Sha256(const char* path, char* outHex);
}
