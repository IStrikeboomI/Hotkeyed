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
#include "Mapping.h"

#pragma comment (lib,"Hid.lib")
//Singleton class that holds all the raw devices
class DeviceManager {
private:
	//we don't need a public constructor because this is a SINGLETON
	DeviceManager();
public:
	std::set<std::shared_ptr<Device>> devices;
	//Adds all mice and keyboard to device set
	void populate();
	void refreshDevices();
	void setMapping(Mapping& mapping);

	static DeviceManager& getInstance();
	//don't implement these two or else we might get multiple copies
	DeviceManager(const DeviceManager&) = delete;
	void operator=(const DeviceManager&) = delete;
};