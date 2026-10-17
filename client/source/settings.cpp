#include "settings.h"
#include "config.h"
#include <xtl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char Settings::language[8] = "en";
bool Settings::videoEnabled = true;
int  Settings::videoVolume = 80;

static void GetSettingsPath(char* out, int outLen) {
    snprintf(out, outLen, "Hdd:\\RiftX\\settings.ini");
}

void Settings::Load() {
    char path[256];
    GetSettingsPath(path, sizeof(path));

    FILE* f = fopen(path, "r");
    if (!f) return;

    char line[128];
    while (fgets(line, sizeof(line), f)) {
        size_t len = strlen(line);
        while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r')) line[--len] = 0;

        char* eq = strchr(line, '=');
        if (!eq) continue;
        *eq = 0;
        char* key = line;
        char* val = eq + 1;
        while (*val == ' ') val++;

        if (strcmp(key, "language") == 0) {
            strncpy(language, val, sizeof(language) - 1);
            language[sizeof(language) - 1] = 0;
        }
        else if (strcmp(key, "video_enabled") == 0) videoEnabled = (strcmp(val, "true") == 0);
        else if (strcmp(key, "video_volume") == 0) videoVolume = atoi(val);
    }
    fclose(f);
}

void Settings::Save() {
    CreateDirectory("Hdd:\\RiftX", nullptr);
    char path[256];
    GetSettingsPath(path, sizeof(path));

    FILE* f = fopen(path, "w");
    if (!f) return;

    fprintf(f, "language=%s\n", language);
    fprintf(f, "video_enabled=%s\n", videoEnabled ? "true" : "false");
    fprintf(f, "video_volume=%d\n", videoVolume);
    fclose(f);
}

void Settings::SetLanguage(const char* langCode) {
    strncpy(language, langCode, sizeof(language) - 1);
    language[sizeof(language) - 1] = 0;
    Save();
}
