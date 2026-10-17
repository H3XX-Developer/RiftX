// ============================================================
// RiftX — Xbox 360 Launcher
// riftxboot.mp4 plays fully on launch — cannot be skipped.
// Multi-language support with persistent settings.
// ============================================================

#include <xtl.h>
#include <xboxmath.h>

#include "config.h"
#include "version.h"
#include "logger.h"
#include "store.h"
#include "video.h"
#include "lang.h"
#include "settings.h"
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
    Settings::Load();

    // Use saved language if set, otherwise use default
    const char* langCode = Settings::language[0] ? Settings::language : Config::DefaultLang();
    Lang::Init(langCode);

    Renderer::Init();
    Theme::Apply();
    Input::Init();

    if (Settings::videoEnabled) {
        Video::PlayIntro(Settings::videoVolume, Config::SkipOnInput());
    }

    while (true) {
        ScreenStore::Show(g_state);
    }
}
