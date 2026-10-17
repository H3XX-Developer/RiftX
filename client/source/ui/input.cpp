#include "input.h"
#include <xtl.h>

static XINPUT_STATE g_prev = {0};
static XINPUT_STATE g_curr = {0};

void Input::Init() { XInputEnable(TRUE); }
void Input::Update() { g_prev = g_curr; XInputGetState(0, &g_curr); }

static WORD Map(Button b) {
    switch (b) {
        case BTN_A: return XINPUT_GAMEPAD_A;
        case BTN_B: return XINPUT_GAMEPAD_B;
        case BTN_X: return XINPUT_GAMEPAD_X;
        case BTN_Y: return XINPUT_GAMEPAD_Y;
        case BTN_START: return XINPUT_GAMEPAD_START;
        case BTN_BACK: return XINPUT_GAMEPAD_BACK;
        case BTN_UP: return XINPUT_GAMEPAD_DPAD_UP;
        case BTN_DOWN: return XINPUT_GAMEPAD_DPAD_DOWN;
        case BTN_LEFT: return XINPUT_GAMEPAD_DPAD_LEFT;
        case BTN_RIGHT: return XINPUT_GAMEPAD_DPAD_RIGHT;
    }
    return 0;
}

bool Input::Pressed(Button b) {
    WORD m = Map(b);
    return (g_curr.Gamepad.wButtons & m) && !(g_prev.Gamepad.wButtons & m);
}
bool Input::Held(Button b) { return (g_curr.Gamepad.wButtons & Map(b)) != 0; }
bool Input::AnyButton() { return g_curr.Gamepad.wButtons != 0; }
