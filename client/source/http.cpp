#include "http.h"
#include "config.h"
#include <xtl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Http::Init() {
    // XNetStartup — usually handled by dashboard
}

HttpResponse Http::Get(const char* url) {
    HttpResponse r = { 0, nullptr, 0 };
    // TODO: real XDK HTTP GET (XNetHttpRequest / XHttpRequest)
    return r;
}

void Http::Free(HttpResponse& r) {
    if (r.body) { free(r.body); r.body = nullptr; r.bodyLen = 0; }
}
