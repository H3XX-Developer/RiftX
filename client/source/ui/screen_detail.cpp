#include "screen_detail.h"
#include "renderer.h"
#include "theme.h"

void ScreenDetail::Show(const char* itemId) {
    Renderer::BeginFrame();
    Renderer::DrawText(50, 50, "Detail", Theme::Gold);
    Renderer::DrawText(50, 100, itemId, Theme::Text);
    Renderer::EndFrame();
}
