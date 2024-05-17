#include "DeviceKey.h"

std::ostream& operator<<(std::ostream& out, const DeviceKey& c) {
    out << c.names.at(0);
    return out;
}
std::wostream& operator<<(std::wostream& out, const DeviceKey& c) {
    std::string temp{ c.names.at(0) };
    out << std::wstring(temp.begin(), temp.end());
    return out;
}

bool DeviceKey::operator<(const DeviceKey& rhs) const {
    return this->value < rhs.value;
}
