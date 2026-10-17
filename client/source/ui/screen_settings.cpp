#include "screen_settings.h"
#include "renderer.h"
#include "theme.h"

void ScreenSettings::Show() {
    Renderer::BeginFrame();
    Renderer::DrawText(50, 50, "Settings", Theme::Gold);
    Renderer::EndFrame();
}
