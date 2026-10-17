#include "renderer.h"
#include <xtl.h>
#include <d3d9.h>

static LPDIRECT3DDEVICE9 g_device = nullptr;

bool Renderer::Init() { return true; }

void Renderer::BeginFrame() {
    if (g_device) {
        g_device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
            D3DCOLOR_ARGB(255, 8, 4, 15), 1.0f, 0);
        g_device->BeginScene();
    }
}

void Renderer::EndFrame() {
    if (g_device) { g_device->EndScene(); g_device->Present(nullptr, nullptr, nullptr, nullptr); }
}

void Renderer::DrawRect(float x, float y, float w, float h, Color c) { /* TODO */ }
void Renderer::DrawText(float x, float y, const char* text, Color c) { /* TODO */ }
void Renderer::DrawImage(const char* path, float x, float y, float w, float h) { /* TODO */ }
