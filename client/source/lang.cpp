#include "lang.h"
#include "json.h"
#include <xtl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../resources/lang/resource.h"

struct LangEntry {
    char key[64];
    char value[256];
};

static LangEntry g_entries[512];
static int g_entryCount = 0;
static char g_current[8] = "en";

struct LangInfo {
    const char* code;
    const char* name;
    int resourceId;
};

static const LangInfo LANGUAGES[] = {
    { "en", "English",    IDR_LANG_EN },
    { "es", "Espanol",    IDR_LANG_ES },
    { "fr", "Francais",   IDR_LANG_FR },
    { "de", "Deutsch",    IDR_LANG_DE },
    { "it", "Italiano",   IDR_LANG_IT },
    { "pt", "Portugues",  IDR_LANG_PT },
    { "ru", "Russkiy",    IDR_LANG_RU },
    { "ja", "Nihongo",    IDR_LANG_JA },
    { "zh", "Zhongwen",   IDR_LANG_ZH },
};
static const int LANG_COUNT = sizeof(LANGUAGES) / sizeof(LANGUAGES[0]);

// Load a language JSON from the embedded resource into memory.
// Returns nullptr on failure.
static char* LoadLangResource(int resourceId, int* outLen) {
    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(resourceId), "BINARY");
    if (!hRes) return nullptr;

    HGLOBAL hData = LoadResource(NULL, hRes);
    if (!hData) return nullptr;

    void* pData = LockResource(hData);
    DWORD size = SizeofResource(NULL, hRes);
    if (!pData || size == 0) return nullptr;

    char* buf = (char*)malloc(size + 1);
    if (!buf) return nullptr;
    memcpy(buf, pData, size);
    buf[size] = 0;
    *outLen = (int)size;
    return buf;
}

static int FindLangResource(const char* code) {
    if (!code) return LANGUAGES[0].resourceId;
    for (int i = 0; i < LANG_COUNT; i++) {
        if (strcmp(LANGUAGES[i].code, code) == 0) return LANGUAGES[i].resourceId;
    }
    return LANGUAGES[0].resourceId;
}

static void ParseInto(LangEntry* out, int* count, const char* data, int max) {
    #define MAX_TOKENS 4096
    static JsonToken tokens[MAX_TOKENS];
    int n = Json::Parse(data, (int)strlen(data), tokens, MAX_TOKENS);
    if (n <= 0) return;

    for (int i = 0; i < n && *count < max; i++) {
        if (tokens[i].type == JSON_STRING && i + 1 < n && tokens[i + 1].type == JSON_STRING) {
            int klen = tokens[i].size < 64 ? tokens[i].size : 63;
            strncpy(out[*count].key, tokens[i].start, klen);
            out[*count].key[klen] = 0;

            int vlen = tokens[i + 1].size < 256 ? tokens[i + 1].size : 255;
            strncpy(out[*count].value, tokens[i + 1].start, vlen);
            out[*count].value[vlen] = 0;

            (*count)++;
            i++;
        }
    }
}

static void LoadLanguage(const char* code) {
    g_entryCount = 0;
    strncpy(g_current, code ? code : "en", sizeof(g_current) - 1);
    g_current[sizeof(g_current) - 1] = 0;

    int id = FindLangResource(g_current);
    int len = 0;
    char* data = LoadLangResource(id, &len);
    if (!data) {
        // Fallback to English
        strcpy(g_current, "en");
        data = LoadLangResource(LANGUAGES[0].resourceId, &len);
    }
    if (!data) return;

    ParseInto(g_entries, &g_entryCount, data, 512);
    free(data);
}

void Lang::Init(const char* langCode) {
    LoadLanguage(langCode);
}

const char* Lang::T(const char* key) {
    if (!key) return "";
    for (int i = 0; i < g_entryCount; i++) {
        if (strcmp(g_entries[i].key, key) == 0) return g_entries[i].value;
    }
    return key;
}

const char* Lang::Current() { return g_current; }

int Lang::Count() { return LANG_COUNT; }

const char* Lang::CodeAt(int i) {
    return (i >= 0 && i < LANG_COUNT) ? LANGUAGES[i].code : "en";
}

const char* Lang::NameAt(int i) {
    return (i >= 0 && i < LANG_COUNT) ? LANGUAGES[i].name : "English";
}
