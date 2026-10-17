// ============================================================
// RiftX — Xbox 360 Launcher
// riftxboot.mp4 plays fully on launch — cannot be skipped.
// ============================================================

#include <xtl.h>
#include <xboxmath.h>

#include "config.h"
#include "version.h"
#include "logger.h"
#include "store.h"
#include "video.h"
#include "ui/renderer.h"
#include "ui/input.h"
#include "ui/theme.h"
#include "ui/screen_store.h"

struct AppState {
    char currentTab[32] = "games";
};

AppState g_state;

void __cdecl main() {
    Logger::Init();
    Renderer::Init();
    Theme::Apply();
    Input::Init();

    if (Config::VideoEnabled()) {
        Video::PlayIntro(Config::VideoVolume(), Config::SkipOnInput());
    }

    while (true) {
        ScreenStore::Show(g_state);
    }
}
