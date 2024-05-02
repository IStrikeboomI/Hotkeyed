#include "DeviceKey.h"

std::ostream& operator<<(std::ostream& out, const DeviceKey& c) {
    out << c.names.at(0);
    return out;
}

bool DeviceKey::operator<(const DeviceKey& rhs) const {
    return this->value < rhs.value;
}
