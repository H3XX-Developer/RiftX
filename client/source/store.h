#pragma once

struct StoreItem {
    char id[64];
    char name[128];
    char category[32];
    char latest[16];
    char description[256];
    char icon[256];
    char download[512];
    char sha256[65];
    long size;
};

namespace Store {
    int FetchApps(StoreItem** out);
    int FetchGames(StoreItem** out);
    void Free(StoreItem* items);
}
