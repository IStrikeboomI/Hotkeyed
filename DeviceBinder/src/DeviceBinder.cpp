#include <iostream>
#include <device/DeviceManager.h>

#pragma comment (lib,"Hotkeyed.lib")
int main() {
	DeviceManager::populate();
	DeviceManager::createOrApplyMapping("mapping.mapping");
	std::cout << DeviceManager::devices.size() << "\n";
	return 0;
}