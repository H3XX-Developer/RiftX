#pragma once

namespace Cache {
    bool Read(const char* name, char* out, int outLen);
    bool Write(const char* name, const char* data, int dataLen);
    void Clear();
}
