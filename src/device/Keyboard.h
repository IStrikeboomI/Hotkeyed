#pragma once
#include "Device.h"
class Keyboard : public Device{
public:
	RID_DEVICE_INFO_KEYBOARD info;

	Keyboard(unsigned int id, std::string deviceInterfaceName, std::wstring productName, std::wstring manufacturerName, HANDLE device, RID_DEVICE_INFO_KEYBOARD info);
};

