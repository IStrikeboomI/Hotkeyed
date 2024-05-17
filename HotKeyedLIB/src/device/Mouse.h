#pragma once
#include "Device.h"
class Mouse : public Device {
public:
	RID_DEVICE_INFO_MOUSE info;

	Mouse(unsigned int id, const std::string& deviceInterfaceName, const std::wstring& productName, const std::wstring& manufacturerName, const HANDLE& device, const RID_DEVICE_INFO_MOUSE& info);
};

