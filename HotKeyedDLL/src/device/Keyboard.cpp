#include "Keyboard.h"

Keyboard::Keyboard(unsigned int id,const std::string& deviceInterfaceName, const std::wstring& productName,const std::wstring& manufacturerName, const HANDLE& device, const RID_DEVICE_INFO_KEYBOARD& info) : Device(id,deviceInterfaceName,productName,manufacturerName,device, RIM_TYPEKEYBOARD), info(info) {
	
}
