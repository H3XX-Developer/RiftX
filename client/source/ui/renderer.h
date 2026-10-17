#pragma once
#include "theme.h"

namespace Renderer {
    bool Init();
    void BeginFrame();
    void EndFrame();
    void DrawRect(float x, float y, float w, float h, Color c);
    void DrawText(float x, float y, const char* text, Color c);
    void DrawImage(const char* path, float x, float y, float w, float h);
}
