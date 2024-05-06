#include "Device.h"

Device::Device(unsigned int id, const std::string& deviceInterfaceName, const std::wstring& productName, const std::wstring& manufacturerName, const HANDLE& device, const byte type) :
	id(id),
	deviceInterfaceName(deviceInterfaceName),
	productName(productName),
	manufacturerName(manufacturerName),
	device(device),
	type(type) {

}

std::wostream& operator<<(std::wostream& out, const Device& c) {
	out << "["
		<< "id = " << c.id
		<< ", deviceInterfaceName = " << c.deviceInterfaceName.c_str()
		<< ", productName=" << c.productName
		<< ", manufacturerName=" << c.manufacturerName
		<< ", type=" << c.type
		<< "]";
	return out;
}
