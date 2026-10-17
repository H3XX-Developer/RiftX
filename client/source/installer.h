#pragma once

namespace Installer {
    bool Install(const char* sourcePath, const char* installDir, const char* expectedSha256);
    bool Uninstall(const char* installDir, const char* id);
}
