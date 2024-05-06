 #include <iostream>
#include "windows/Interceptor.h"
#include "hotkey/HotkeyManager.h"
#include "keyboard/DeviceKeys.h"
#include <filesystem>
#include <process.h>
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason,LPVOID lpvReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH: {
            DeviceManager::populate();
            DeviceManager::createOrApplyMapping("mapping.mapping");
            Interceptor interceptor;
            interceptor.begin();
            break;
        }

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;

        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
