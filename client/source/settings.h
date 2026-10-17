#pragma once

struct Settings {
    static char language[8];
    static bool videoEnabled;
    static int  videoVolume;

    static void Load();
    static void Save();
    static void SetLanguage(const char* langCode);
};
