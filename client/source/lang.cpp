#include "lang.h"
#include "json.h"
#include <xtl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// All 9 languages are embedded in the XEX as resource strings.
// We load them into a small in-memory dictionary on Init().

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
    const char* data;
};

// These symbols are defined by lang.rc — one per language.
extern const char* LANG_EN_DATA;
extern const char* LANG_ES_DATA;
extern const char* LANG_FR_DATA;
extern const char* LANG_DE_DATA;
extern const char* LANG_IT_DATA;
extern const char* LANG_PT_DATA;
extern const char* LANG_RU_DATA;
extern const char* LANG_JA_DATA;
extern const char* LANG_ZH_DATA;

static const LangInfo LANGUAGES[] = {
    { "en", "English",    LANG_EN_DATA },
    { "es", "Español",    LANG_ES_DATA },
    { "fr", "Français",   LANG_FR_DATA },
    { "de", "Deutsch",    LANG_DE_DATA },
    { "it", "Italiano",   LANG_IT_DATA },
    { "pt", "Português",  LANG_PT_DATA },
    { "ru", "Русский",    LANG_RU_DATA },
    { "ja", "日本語",      LANG_JA_DATA },
    { "zh", "中文",        LANG_ZH_DATA },
};
static const int LANG_COUNT = sizeof(LANGUAGES) / sizeof(LANGUAGES[0]);

static const char* FindLanguageData(const char* code) {
    for (int i = 0; i < LANG_COUNT; i++) {
        if (strcmp(LANGUAGES[i].code, code) == 0) return LANGUAGES[i].data;
    }
    return LANGUAGES[0].data;  // fallback to English
}

static void ParseInto(LangEntry* out, int* count, const char* data, int max) {
    #define MAX_TOKENS 4096
    static JsonToken tokens[MAX_TOKENS];
    int n = Json::Parse(data, (int)strlen(data), tokens, MAX_TOKENS);
    if (n <= 0) return;

    for (int i = 0; i < n && *count < max; i++) {
        if (tokens[i].type == JSON_STRING && i + 1 < n && tokens[i + 1].type == JSON_STRING) {
            // Every other string is a key-value pair
            int klen = tokens[i].size < 64 ? tokens[i].size : 63;
            strncpy(out[*count].key, tokens[i].start, klen);
            out[*count].key[klen] = 0;

            int vlen = tokens[i + 1].size < 256 ? tokens[i + 1].size : 255;
            strncpy(out[*count].value, tokens[i + 1].start, vlen);
            out[*count].value[vlen] = 0;

            (*count)++;
            i++;  // skip value token
        }
    }
}

void Lang::Init(const char* langCode) {
    strncpy(g_current, langCode ? langCode : "en", sizeof(g_current) - 1);
    g_entryCount = 0;

    const char* data = FindLanguageData(g_current);
    ParseInto(g_entries, &g_entryCount, data, 512);

    // If the chosen language didn't load anything, try English
    if (g_entryCount == 0 && strcmp(g_current, "en") != 0) {
        strcpy(g_current, "en");
        ParseInto(g_entries, &g_entryCount, LANG_EN_DATA, 512);
    }
}

const char* Lang::T(const char* key) {
    if (!key) return "";

    for (int i = 0; i < g_entryCount; i++) {
        if (strcmp(g_entries[i].key, key) == 0) return g_entries[i].value;
    }

    // Fallback: return the key itself so missing strings are visible
    return key;
}

const char* Lang::Current() { return g_current; }
int Lang::Count() { return LANG_COUNT; }
const char* Lang::CodeAt(int i) { return (i >= 0 && i < LANG_COUNT) ? LANGUAGES[i].code : "en"; }
const char* Lang::NameAt(int i) { return (i >= 0 && i < LANG_COUNT) ? LANGUAGES[i].name : "English"; }
