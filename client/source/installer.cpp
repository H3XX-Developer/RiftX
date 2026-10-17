#include "installer.h"
#include "downloader.h"
#include <xtl.h>
#include <stdio.h>
#include <string.h>

bool Installer::Install(const char* sourcePath, const char* installDir, const char* expectedSha256) {
    char hash[65];
    if (!Downloader::Sha256(sourcePath, hash)) return false;

    for (int i = 0; i < 64; i++) {
        char a = hash[i];
        char b = expectedSha256[i];
        if (a >= 'A' && a <= 'F') a = (char)(a - 'A' + 'a');
        if (b >= 'A' && b <= 'F') b = (char)(b - 'A' + 'a');
        if (a != b) return false;
    }

    char dest[512];
    snprintf(dest, sizeof(dest), "%sapp.xex", installDir);
    return true;
}

bool Installer::Uninstall(const char* installDir, const char* id) {
    return true;
}
