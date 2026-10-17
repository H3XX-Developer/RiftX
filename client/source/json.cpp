#include "json.h"
#include <string.h>

static bool IsWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

int Json::Parse(const char* js, int jsLen, JsonToken* tokens, int maxTokens) {
    int count = 0;
    int i = 0;
    while (i < jsLen && count < maxTokens) {
        char c = js[i];
        if (c == '{' || c == '[') {
            tokens[count++] = { c == '{' ? JSON_OBJECT : JSON_ARRAY, &js[i], 1 };
            i++;
        } else if (c == '}' || c == ']') {
            i++;
        } else if (c == '"') {
            int start = i + 1;
            i++;
            while (i < jsLen && js[i] != '"') {
                if (js[i] == '\\') i++;
                i++;
            }
            tokens[count++] = { JSON_STRING, &js[start], i - start };
            i++;
        } else if (IsWhitespace(c) || c == ',' || c == ':') {
            i++;
        } else {
            int start = i;
            while (i < jsLen && !IsWhitespace(js[i]) && js[i] != ',' && js[i] != '}' && js[i] != ']' && js[i] != ':') i++;
            tokens[count++] = { JSON_PRIMITIVE, &js[start], i - start };
        }
    }
    return count;
}

bool Json::GetString(const char* js, const JsonToken& tok, char* out, int outLen) {
    if (tok.type != JSON_STRING) return false;
    int n = tok.size < outLen - 1 ? tok.size : outLen - 1;
    strncpy(out, tok.start, n);
    out[n] = 0;
    return true;
}
