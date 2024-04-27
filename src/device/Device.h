#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
class Device {
public:
	unsigned int id = 0;
	const std::string deviceInterfaceName;
	const std::wstring productName;
	const std::wstring manufacturerName;
	//RIM_TYPEKEYBOARD (1) for keyboard
	//RIM_TYPEMOUSE (0) for mouse
	const byte type;
	const HANDLE device;

	Device(unsigned int id, const std::string& deviceInterfaceName, const std::wstring& productName, const std::wstring& manufacturerName,const HANDLE& device, const byte type);
	friend std::wostream& operator<<(std::wostream& out, const Device& c);
};

