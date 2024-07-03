#include "DeviceManager.h"

DeviceManager::DeviceManager() {
	populate();
}
void DeviceManager::populate() {
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
			Keyboard keyboard(currentDeviceId++, std::string(n), std::wstring(name), std::wstring(manufacturer), r.hDevice, info.keyboard);
			devices.emplace(std::make_shared<Keyboard>(keyboard));
		}
		if (r.dwType == RIM_TYPEMOUSE) {
			Mouse mouse(currentDeviceId++, std::string(n), std::wstring(name), std::wstring(manufacturer), r.hDevice, info.mouse);
			devices.emplace(std::make_shared<Mouse>(mouse));
		}
	}
}
void DeviceManager::refreshDevices() {
	devices.clear();
	populate();
}
void DeviceManager::setMapping(Mapping& mapping) {
	for (auto const& [key, val] : mapping.mapping) {
		for (std::shared_ptr<Device> d : devices) {
			if (d->deviceInterfaceName==key) {
				d->id = val;
			}
		}
	}
}
DeviceManager& DeviceManager::getInstance() {
	// TODO: insert return statement here
	static DeviceManager instance;
	return instance;
}
