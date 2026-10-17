#include "screen_store.h"
#include "../store.h"
#include "../logger.h"
#include "renderer.h"
#include "input.h"
#include "theme.h"

void ScreenStore::Show(AppState& state) {
    Input::Update();

    StoreItem* items = nullptr;
    int count = Store::FetchApps(&items);
    Logger::Info("Loaded %d apps from catalog", count);

    Renderer::BeginFrame();
    Renderer::DrawText(50, 50, "RIFTX", Theme::Gold);
    Renderer::DrawText(50, 90, "Store", Theme::BlueLight);

    // TODO: render tile grid using Theme::Gold / Theme::BlueLight

    Renderer::EndFrame();

    Store::Free(items);
}
