#pragma once
#include "Device.h"
class Keyboard : public Device{
public:
	RID_DEVICE_INFO_KEYBOARD info;

	Keyboard(unsigned int id, const std::string& deviceInterfaceName, const std::wstring& productName, const std::wstring& manufacturerName, const HANDLE& device, const RID_DEVICE_INFO_KEYBOARD& info);
};

