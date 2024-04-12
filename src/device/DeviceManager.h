#pragma once
#include <set>
#include <memory>
#include "Device.h"
#include "Keyboard.h"
#include <Windows.h>
#include <Ntddkbd.h>
#include <string>
#include <Hidsdi.h>

#pragma comment (lib,"Hid.lib")
namespace DeviceManager {
	extern std::set<std::shared_ptr<Device>> devices;
	//Adds all mice and keyboard to device set
	static void populate() {
		unsigned int currentDeviceId = 0;
		RAWINPUTDEVICELIST d[128];
		unsigned int numDevices = sizeof(d);
		GetRawInputDeviceList(d, &numDevices, sizeof(RAWINPUTDEVICELIST));
		for (RAWINPUTDEVICELIST r : d) {
			RID_DEVICE_INFO info;
			info.cbSize = sizeof(RID_DEVICE_INFO);
			unsigned int RIDsize = sizeof(info);
			unsigned int copied = GetRawInputDeviceInfoA(r.hDevice, RIDI_DEVICEINFO, &info, &RIDsize);

			char n[0xFF];
			unsigned int nameSize = sizeof(n);
			int charCopied = GetRawInputDeviceInfoA(r.hDevice, RIDI_DEVICENAME, &n, &nameSize);
			if (charCopied != -1) {
				n[charCopied] = '\0';
			}

			wchar_t name[0xFF];
			wchar_t manufacturer[0xFF];
			HANDLE device = CreateFileA(n, NULL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
			HidD_GetProductString(device, name, sizeof(name));
			HidD_GetManufacturerString(device, manufacturer, sizeof(manufacturer));
			CloseHandle(device);
			if (r.dwType == RIM_TYPEKEYBOARD) {
				Keyboard keyboard(currentDeviceId++,std::string(n),std::wstring(name),std::wstring(manufacturer),r.hDevice,info.keyboard);
				devices.insert(std::make_shared<Keyboard>(keyboard));
			}
			if (r.dwType == RIM_TYPEMOUSE) {

			}
		}
	}
}