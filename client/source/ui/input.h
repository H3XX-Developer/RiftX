#pragma once

enum Button {
    BTN_A, BTN_B, BTN_X, BTN_Y, BTN_START, BTN_BACK,
    BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT
};

namespace Input {
    void Init();
    void Update();
    bool Pressed(Button b);
    bool Held(Button b);
    bool AnyButton();
}
