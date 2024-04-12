#include "Device.h"

Device::Device(unsigned int id, std::string deviceInterfaceName, std::wstring productName, std::wstring manufacturerName, HANDLE device, byte type) :
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
		<< "deviceInterfaceName = " << c.deviceInterfaceName.c_str()
		<< ", productName=" << c.productName
		<< ", manufacturerName=" << c.manufacturerName
		<< ", type=" << c.type
		<< "]";
	return out;
}
