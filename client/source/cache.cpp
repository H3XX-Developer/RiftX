#include "cache.h"
#include "config.h"
#include <xtl.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

static void BuildPath(const char* name, char* out, int outLen) {
    snprintf(out, outLen, "%s%s.cache", Config::CacheDir(), name);
}

bool Cache::Read(const char* name, char* out, int outLen) {
    char path[256];
    BuildPath(name, path, sizeof(path));

    WIN32_FILE_ATTRIBUTE_DATA fad;
    if (!GetFileAttributesEx(path, GetFileExInfoStandard, &fad)) return false;

    FILETIME now;
    GetSystemTimeAsFileTime(&now);
    ULARGE_INTEGER nowU, wroteU;
    nowU.LowPart = now.dwLowDateTime; nowU.HighPart = now.dwHighDateTime;
    wroteU.LowPart = fad.ftLastWriteTime.dwLowDateTime;
    wroteU.HighPart = fad.ftLastWriteTime.dwHighDateTime;

    ULONGLONG diffSeconds = (nowU.QuadPart - wroteU.QuadPart) / 10000000ULL;
    if (diffSeconds > (ULONGLONG)Config::CacheHours() * 3600ULL) return false;

    FILE* f = fopen(path, "rb");
    if (!f) return false;
    int n = (int)fread(out, 1, outLen - 1, f);
    out[n] = 0;
    fclose(f);
    return true;
}

bool Cache::Write(const char* name, const char* data, int dataLen) {
    CreateDirectory("Hdd:\\RiftX", nullptr);
    CreateDirectory(Config::CacheDir(), nullptr);
    char path[256];
    BuildPath(name, path, sizeof(path));
    FILE* f = fopen(path, "wb");
    if (!f) return false;
    fwrite(data, 1, dataLen, f);
    fclose(f);
    return true;
}

void Cache::Clear() {
    // Delete *.cache files in CacheDir
}
