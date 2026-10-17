#include "logger.h"
#include "config.h"
#include <xtl.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

static FILE* g_log = nullptr;

static void WriteLine(const char* level, const char* fmt, va_list args) {
    if (!g_log) return;
    time_t t = time(nullptr);
    struct tm* tm = localtime(&t);
    fprintf(g_log, "[%04d-%02d-%02d %02d:%02d:%02d] [%s] ",
        tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
        tm->tm_hour, tm->tm_min, tm->tm_sec, level);
    vfprintf(g_log, fmt, args);
    fprintf(g_log, "\n");
    fflush(g_log);
}

void Logger::Init() {
    CreateDirectory("Hdd:\\RiftX", nullptr);
    CreateDirectory(Config::LogDir(), nullptr);
    char path[256];
    snprintf(path, sizeof(path), "%slauncher.log", Config::LogDir());
    g_log = fopen(path, "a");
}

void Logger::Info(const char* fmt, ...) { va_list a; va_start(a, fmt); WriteLine("INFO", fmt, a); va_end(a); }
void Logger::Warn(const char* fmt, ...) { va_list a; va_start(a, fmt); WriteLine("WARN", fmt, a); va_end(a); }
void Logger::Error(const char* fmt, ...) { va_list a; va_start(a, fmt); WriteLine("ERROR", fmt, a); va_end(a); }
