#include "video.h"
#include <xtl.h>
#include <xmedia.h>
#include "../resources/video/resource.h"

bool Video::PlayIntro(int volumePercent, bool skipOnInput) {
    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(IDR_RIFTXBOOT_MP4), "MP4");
    if (!hRes) return false;

    HGLOBAL hData = LoadResource(NULL, hRes);
    if (!hData) return false;

    void* pData = LockResource(hData);
    DWORD size = SizeofResource(NULL, hRes);
    if (!pData || size == 0) return false;

    // XMedia playback from memory — fill in when building with XDK
    // XMediaInitialize();
    // XMediaOpenFromMemory(pData, size, ...);
    // XMediaSetVolume(volumePercent);
    // XMediaPlay();

    bool playing = true;
    while (playing) {
        // XMediaRenderFrame();
        if (skipOnInput) {
            XINPUT_STATE state;
            if (XInputGetState(0, &state) == ERROR_SUCCESS) {
                if (state.Gamepad.wButtons != 0) break;
            }
        }
        // if (XMediaIsFinished()) playing = false;
        Sleep(16);
    }

    // XMediaStop();
    // XMediaClose();
    // XMediaShutdown();

    return true;
}
