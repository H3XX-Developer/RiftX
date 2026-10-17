#pragma once

enum JsonType { JSON_UNDEFINED = 0, JSON_OBJECT, JSON_ARRAY, JSON_STRING, JSON_PRIMITIVE };

struct JsonToken {
    JsonType type;
    const char* start;
    int size;
};

namespace Json {
    int Parse(const char* js, int jsLen, JsonToken* tokens, int maxTokens);
    bool GetString(const char* js, const JsonToken& tok, char* out, int outLen);
}
