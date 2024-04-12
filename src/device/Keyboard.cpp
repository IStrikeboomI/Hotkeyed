#include "Keyboard.h"

Keyboard::Keyboard(unsigned int id, std::string deviceInterfaceName, std::wstring productName, std::wstring manufacturerName, HANDLE device, RID_DEVICE_INFO_KEYBOARD info) : Device(id,deviceInterfaceName,productName,manufacturerName,device, RIM_TYPEKEYBOARD), info(info) {
	
}
