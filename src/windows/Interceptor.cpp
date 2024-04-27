#include "Interceptor.h"
#include "../hotkey/DeviceKeys.h"
LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {return DefWindowProcW(hwnd, msg, wparam, lparam);}

void Interceptor::handleInput(const MSG& msg) {
	RAWINPUT input;
	unsigned int size = sizeof(input);
	GetRawInputData((HRAWINPUT)msg.lParam, RID_INPUT, &input, &size, sizeof(RAWINPUTHEADER));

	char name[256];
	unsigned int nameSize = sizeof(name);
	unsigned int copied = GetRawInputDeviceInfoA(input.header.hDevice, RIDI_DEVICENAME, &name, &nameSize);
	for (std::shared_ptr<Device> d : DeviceManager::devices) {
		if (d->deviceInterfaceName == name) {
			if (d->type == RIM_TYPEKEYBOARD) {
				Keyboard* keyboard = static_cast<Keyboard*>(d.get());
				for (auto callback : keyboardGlobalInterceptors) {
					callback(*keyboard, input.data.keyboard.Flags == 0 ? DOWN : UP, DeviceKeys::getByVKey(input.data.keyboard.VKey));
				}
			}
		}
	}
}
Interceptor::Interceptor() : keyboardGlobalInterceptors(), wc({0}) {
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = L"hotkeyed";
	wc.lpfnWndProc = windowProcedure;
	wc.lpszMenuName = L"Hotkeyed";
	if (!RegisterClass(&wc)) {
		throw std::runtime_error("Could not register class");
	}
}

void Interceptor::begin() {
	//Creates Window
	HWND hwnd = CreateWindow(wc.lpszClassName, wc.lpszMenuName, 0, 0, 0, 0, 0, nullptr, nullptr, wc.hInstance, nullptr);

	//register raw devices
	RAWINPUTDEVICE keyboards[1];
	keyboards[0].usUsagePage = 1;
	keyboards[0].usUsage = 6;
	keyboards[0].dwFlags = RIDEV_INPUTSINK;
	keyboards[0].hwndTarget = hwnd;
	if (RegisterRawInputDevices(keyboards, 1, sizeof(keyboards[0]))) {
		//SetWindowsHookExA(WH_KEYBOARD_LL,LowLevelKeyBoardProc,GetModuleHandle(nullptr),0);
		MSG msg = { nullptr };

		while (GetMessageW(&msg, nullptr, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
			if (msg.message == WM_INPUT) {
				handleInput(msg);
			}
		}
	} else {
		throw std::runtime_error("Could not register devices");
	}
}
