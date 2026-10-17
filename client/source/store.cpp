#include "store.h"
#include "http.h"
#include "cache.h"
#include "json.h"
#include "config.h"
#include <stdlib.h>
#include <string.h>

static int ParseCatalog(const char* jsonData, int jsonLen, const char* rootKey, StoreItem** out) {
    #define MAX_TOKENS 4096
    static JsonToken tokens[MAX_TOKENS];
    int n = Json::Parse(jsonData, jsonLen, tokens, MAX_TOKENS);
    if (n <= 0) return 0;

    int rootIdx = -1;
    for (int i = 0; i < n; i++) {
        if (tokens[i].type == JSON_STRING && tokens[i].size == (int)strlen(rootKey) &&
            strncmp(tokens[i].start, rootKey, tokens[i].size) == 0) {
            rootIdx = i;
            break;
        }
    }
    if (rootIdx < 0) return 0;

    int arrIdx = -1;
    for (int i = rootIdx + 1; i < n; i++) {
        if (tokens[i].type == JSON_ARRAY) { arrIdx = i; break; }
    }
    if (arrIdx < 0) return 0;

    int count = 0;
    for (int i = arrIdx + 1; i < n; i++) {
        if (tokens[i].type == JSON_STRING && tokens[i].size == 2 &&
            strncmp(tokens[i].start, "id", 2) == 0) count++;
    }

    StoreItem* items = (StoreItem*)calloc(count, sizeof(StoreItem));
    int idx = 0;
    for (int i = arrIdx + 1; i < n && idx < count; i++) {
        if (tokens[i].type == JSON_STRING && tokens[i].size == 2 &&
            strncmp(tokens[i].start, "id", 2) == 0 && i + 1 < n) {
            Json::GetString(jsonData, tokens[i + 1], items[idx].id, sizeof(items[idx].id));
            idx++;
        }
    }

    *out = items;
    return count;
}

int Store::FetchApps(StoreItem** out) {
    char cached[65536];
    if (Cache::Read("apps", cached, sizeof(cached)))
        return ParseCatalog(cached, (int)strlen(cached), "apps", out);
    HttpResponse r = Http::Get(Config::AppsUrl());
    if (r.status != 200 || !r.body) { Http::Free(r); return 0; }
    Cache::Write("apps", r.body, r.bodyLen);
    int count = ParseCatalog(r.body, r.bodyLen, "apps", out);
    Http::Free(r);
    return count;
}

int Store::FetchGames(StoreItem** out) {
    char cached[65536];
    if (Cache::Read("games", cached, sizeof(cached)))
        return ParseCatalog(cached, (int)strlen(cached), "games", out);
    HttpResponse r = Http::Get(Config::GamesUrl());
    if (r.status != 200 || !r.body) { Http::Free(r); return 0; }
    Cache::Write("games", r.body, r.bodyLen);
    int count = ParseCatalog(r.body, r.bodyLen, "games", out);
    Http::Free(r);
    return count;
}

void Store::Free(StoreItem* items) {
    if (items) free(items);
}
