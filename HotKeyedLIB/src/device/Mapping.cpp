#include "Mapping.h"
#include "DeviceManager.h"
class DeviceManager;
Mapping::Mapping(std::string filename) : filename(filename) {
	if (std::filesystem::exists(filename)) {
		applyMapping();
	} else {
		saveMapping();
	}
}

void Mapping::saveMapping() {
	file = std::fstream(filename, std::ios::out | std::ios::trunc);
	json.clear();
	if (file.is_open()) {
		for (std::shared_ptr<Device> d : DeviceManager::getInstance().devices) {
			nlohmann::json mappingObject;
			mappingObject["deviceInterfaceName"] = d->deviceInterfaceName;
			mappingObject["id"] = d->id;
			json.push_back(mappingObject);
		}
		file << std::setw(3) << json;
	}
	file.close();
}
void Mapping::applyMapping() {
	file = std::fstream(filename, std::ios::in | std::ios::app);
	file >> json;
	if (file.is_open()) {
		for (nlohmann::json object : json) {
			std::string deviceInterfaceName = object["deviceInterfaceName"];
			int id = object["id"];
			mapping.emplace(deviceInterfaceName, id);
		}
	}
	file.close();
}
