#include "Interceptor.h"
#include "../keyboard/DeviceKeys.h"
LRESULT CALLBACK hotkeyedWindProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {return DefWindowProcW(hwnd, msg, wparam, lparam);}

void Interceptor::handleInput(const MSG& msg) {
	RAWINPUT input;
	unsigned int size = sizeof(input);
	GetRawInputData((HRAWINPUT)msg.lParam, RID_INPUT, &input, &size, sizeof(RAWINPUTHEADER));

	char name[256];
	unsigned int nameSize = sizeof(name);
	unsigned int copied = GetRawInputDeviceInfoA(input.header.hDevice, RIDI_DEVICENAME, &name, &nameSize);
	for (std::shared_ptr<Device> d : DeviceManager::devices) {
		if (d->deviceInterfaceName == name) {
			if (input.header.dwType == RIM_TYPEKEYBOARD && d->type == RIM_TYPEKEYBOARD) {
				Keyboard* keyboard = static_cast<Keyboard*>(d.get());
				for (auto callback : keyboardGlobalInterceptors) {
					callback(*keyboard, input.data.keyboard.Flags == 0 ? DOWN : UP, DeviceKeys::getByVKey(input.data.keyboard.VKey));
				}
			}
			if (input.header.dwType == RIM_TYPEMOUSE && d->type == RIM_TYPEMOUSE) {
				POINT pos;
				GetCursorPos(&pos);
				int x = pos.x;
				int y = pos.y;
				Mouse* mouse = static_cast<Mouse*>(d.get());
				for (auto callback : mouseGlobalInterceptors) {
					if (input.data.mouse.usButtonFlags == 0) {
						callback(*mouse, NONE, DeviceKeys::getByVKey(0), x, y);
					}
					if ((input.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN) == RI_MOUSE_LEFT_BUTTON_DOWN) {
						callback(*mouse,DOWN, DeviceKeys::getByVKey(VK_LBUTTON),x,y);
					}
					if ((input.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP) == RI_MOUSE_LEFT_BUTTON_UP) {
						callback(*mouse, UP, DeviceKeys::getByVKey(VK_LBUTTON), x, y);
					}
					if ((input.data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN) == RI_MOUSE_RIGHT_BUTTON_DOWN) {
						callback(*mouse, DOWN, DeviceKeys::getByVKey(VK_RBUTTON), x, y);
					}
					if ((input.data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP) == RI_MOUSE_RIGHT_BUTTON_UP) {
						callback(*mouse, UP, DeviceKeys::getByVKey(VK_RBUTTON), x, y);
					}
					if ((input.data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN) == RI_MOUSE_MIDDLE_BUTTON_DOWN) {
						callback(*mouse, DOWN, DeviceKeys::getByVKey(VK_MBUTTON), x, y);
					}
					if ((input.data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP) == RI_MOUSE_MIDDLE_BUTTON_UP) {
						callback(*mouse, UP, DeviceKeys::getByVKey(VK_MBUTTON), x, y);
					}

				}
			}
		}
	}
}
Interceptor::Interceptor() : keyboardGlobalInterceptors(), wc({0}) {
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = L"hotkeyed";
	wc.lpfnWndProc = hotkeyedWindProc;
	wc.lpszMenuName = L"Hotkeyed";
	if (!RegisterClass(&wc)) {
		throw std::runtime_error("Could not register class");
	}
}

void Interceptor::begin() {
	//Creates Window
	HWND hwnd = CreateWindow(wc.lpszClassName, wc.lpszMenuName, 0, 0, 0, 0, 0, nullptr, nullptr, wc.hInstance, nullptr);

	//register raw devices
	RAWINPUTDEVICE devices[2];
	//keyboard
	devices[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	devices[0].usUsage = HID_USAGE_GENERIC_KEYBOARD;
	devices[0].dwFlags = RIDEV_INPUTSINK;
	devices[0].hwndTarget = hwnd;
	//mouse
	devices[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
	devices[1].usUsage = HID_USAGE_GENERIC_MOUSE;
	devices[1].dwFlags = RIDEV_INPUTSINK;
	devices[1].hwndTarget = hwnd;
	if (RegisterRawInputDevices(devices, 2, sizeof(RAWINPUTDEVICE))) {
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

void Interceptor::end() {
	PostQuitMessage(0);
}
