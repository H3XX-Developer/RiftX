#pragma once

struct Color { float r, g, b, a; };

namespace Theme {
    // Metallic gold palette
    const Color Gold         = { 1.000f, 0.843f, 0.000f, 1.0f };  // #FFD700
    const Color GoldMid      = { 0.855f, 0.647f, 0.125f, 1.0f };  // #DAA520
    const Color GoldDark     = { 0.722f, 0.525f, 0.043f, 1.0f };  // #B8860B
    const Color GoldDeep     = { 0.545f, 0.412f, 0.078f, 1.0f };  // #8B6914

    // Light blue accents
    const Color BlueLight    = { 0.000f, 0.831f, 1.000f, 1.0f };  // #00D4FF
    const Color BlueDark     = { 0.000f, 0.533f, 0.800f, 1.0f };  // #0088CC

    // Background / text
    const Color Bg           = { 0.031f, 0.016f, 0.059f, 1.0f };  // #08040F
    const Color Text         = { 0.960f, 0.960f, 0.980f, 1.0f };
    const Color TextDim      = { 0.722f, 0.722f, 0.784f, 1.0f };

    inline void Apply() {}
}
