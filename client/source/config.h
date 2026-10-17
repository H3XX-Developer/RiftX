#pragma once

struct Config {
    static const char* AppsUrl()      { return "https://YOUR-USERNAME.github.io/RiftX/catalog/apps.json"; }
    static const char* GamesUrl()     { return "https://YOUR-USERNAME.github.io/RiftX/catalog/games.json"; }
    static const char* ManifestUrl()  { return "https://YOUR-USERNAME.github.io/RiftX/updates/manifest.json"; }

    static const char* InstallDir()   { return "Hdd:\\RiftX\\Apps\\"; }
    static const char* DownloadDir()  { return "Hdd:\\RiftX\\Downloads\\"; }
    static const char* CacheDir()     { return "Hdd:\\RiftX\\Cache\\"; }
    static const char* LogDir()       { return "Hdd:\\RiftX\\Logs\\"; }

    static int  TimeoutMs()           { return 15000; }
    static bool AutoCheckUpdates()    { return true; }
    static int  UpdateIntervalHours() { return 6; }
    static int  CacheHours()          { return 24; }

    static bool VideoEnabled()        { return true; }
    static bool SkipOnInput()         { return false; }
    static int  VideoVolume()         { return 80; }
};
