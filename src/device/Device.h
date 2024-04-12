#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
class Device {
public:
	unsigned int id = 0;
	std::string deviceInterfaceName;
	std::wstring productName;
	std::wstring manufacturerName;
	//RIM_TYPEKEYBOARD (1) for keyboard
	//RIM_TYPEMOUSE (0) for mouse
	byte type;
	HANDLE device;

	Device(unsigned int id, std::string deviceInterfaceName, std::wstring productName, std::wstring manufacturerName,HANDLE device, byte type);
	friend std::wostream& operator<<(std::wostream& out, const Device& c);
};

