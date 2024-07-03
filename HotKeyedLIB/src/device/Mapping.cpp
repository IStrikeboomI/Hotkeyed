#include "Mapping.h"
#include "DeviceManager.h"
class DeviceManager;
Mapping::Mapping(std::string filename) : filename(filename) {
	if (std::filesystem::exists(filename)) {
		file = std::fstream(filename, std::ios::out);
		file >> json;
		applyMapping();
	} else {
		file = std::fstream(filename, std::ios::out);
		saveMapping();
	}
}

void Mapping::saveMapping() {
	if (file.is_open()) {
		for (std::shared_ptr<Device> d : DeviceManager::getInstance().devices) {
			nlohmann::json mappingObject;
			mappingObject["deviceInterfaceName"] = d->deviceInterfaceName;
			mappingObject["id"] = d->id;
			json.push_back(mappingObject);
		}
		file << std::setw(3) << json;
	}
}
void Mapping::applyMapping() {
	if (file.is_open()) {
		
	}
}
