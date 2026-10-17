#pragma once

struct HttpResponse {
    int  status;
    char* body;
    int  bodyLen;
};

namespace Http {
    void Init();
    HttpResponse Get(const char* url);
    void Free(HttpResponse& r);
}
