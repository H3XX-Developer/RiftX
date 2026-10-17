#pragma once

namespace Lang {
    void Init(const char* langCode);
    const char* T(const char* key);
    const char* Current();

    int Count();
    const char* CodeAt(int index);
    const char* NameAt(int index);
}
