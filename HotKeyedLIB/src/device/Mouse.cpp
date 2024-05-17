#include "Mouse.h"
Mouse::Mouse(unsigned int id, const std::string& deviceInterfaceName, const std::wstring& productName, const std::wstring& manufacturerName, const HANDLE& device, const RID_DEVICE_INFO_MOUSE& info) : Device(id, deviceInterfaceName, productName, manufacturerName, device, RIM_TYPEMOUSE), info(info) {

}