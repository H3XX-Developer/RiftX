#pragma once
#include <stdlib.h>

namespace Memory {
    extern int g_allocCount;
    inline void* Alloc(size_t n) { g_allocCount++; return malloc(n); }
    inline void* Calloc(size_t n, size_t s) { g_allocCount++; return calloc(n, s); }
    inline void Free(void* p) { if (p) { g_allocCount--; free(p); } }
}
