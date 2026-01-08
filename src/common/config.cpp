#include "common/config.h"
#include <iostream>

namespace common {

Config::Config() 
    : mavlink_port_(14550),
      camera_device_("/dev/video0"),
      drop_altitude_(50.0),
      search_speed_(5.0) {
}

Config::~Config() {
}

bool Config::load(const std::string& config_file) {
    // Stub implementation
    std::cout << "Loading configuration from: " << config_file << std::endl;
    return true;
}

int Config::getMavlinkPort() const {
    return mavlink_port_;
}

std::string Config::getCameraDevice() const {
    return camera_device_;
}

double Config::getDropAltitude() const {
    return drop_altitude_;
}

double Config::getSearchSpeed() const {
    return search_speed_;
}

} // namespace common
