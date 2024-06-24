#pragma once
#include <set>
#include <memory>
#include "Device.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <Windows.h>
#include <Ntddkbd.h>
#include <string>
#include <Hidsdi.h>
#include <filesystem>
#include <fstream>

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
				devices.emplace(std::make_shared<Keyboard>(keyboard));
			}
			if (r.dwType == RIM_TYPEMOUSE) {
				Mouse mouse(currentDeviceId++, std::string(n), std::wstring(name), std::wstring(manufacturer), r.hDevice, info.mouse);
				devices.emplace(std::make_shared<Mouse>(mouse));
			}
		}
	}
	static bool isNumber(const std::string& s) {
		return !s.empty() && std::find_if(s.begin(),
										  s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
	}
	static void saveMapping(const std::string& mappingFile = "") {
		std::fstream file(mappingFile, std::ios::out);
		if (file.is_open()) {
			for (std::shared_ptr<Device> d : devices) {
				file << d->deviceInterfaceName << "=" << d->id << "\n";
			}
		}
		file.close();
	}
	static void applyMapping(const std::string& mappingFile) {
		if (!mappingFile.ends_with(".mapping")) {
			throw std::invalid_argument("Not a mapping file!");
		}
		std::fstream file(mappingFile);
		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {
				std::string deviceInterfaceName = line.substr(0, line.find_last_of("="));
				std::string deviceId = line.substr(line.find_last_of("=") + 1);
				for (std::shared_ptr<Device> d : devices) {
					if (d->deviceInterfaceName == deviceInterfaceName) {
						if (isNumber(deviceId)) {
							d->id = std::stoi(deviceId);
						}
					}
				}
			}
		}
	}
	//If mappingFile is empty or doesn't exist, then create a default mapping which is just the devices in order
	//If file does exist then apply mapping
	static void createOrApplyMapping(const std::string& mappingFile="") {
		if (std::filesystem::exists(mappingFile)) {
			applyMapping(mappingFile);
		} else {
			saveMapping(mappingFile);
		}
	}
}