#pragma once

namespace Lang {
    // Initialize with a language code ("en", "es", "fr", etc.)
    // Falls back to English if the language is not available.
    void Init(const char* langCode);

    // Get the translated string for a key.
    // Falls back to English, then to the key itself.
    const char* T(const char* key);

    // Get current language code
    const char* Current();

    // List of available languages
    int Count();
    const char* CodeAt(int index);
    const char* NameAt(int index);
}
