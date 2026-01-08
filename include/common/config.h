#ifndef COMMON_CONFIG_H
#define COMMON_CONFIG_H

#include <string>

namespace common {

class Config {
public:
    Config();
    ~Config();

    // Load configuration from file
    bool load(const std::string& config_file);
    
    // Get configuration values
    int getMavlinkPort() const;
    std::string getCameraDevice() const;
    double getDropAltitude() const;
    double getSearchSpeed() const;

private:
    int mavlink_port_;
    std::string camera_device_;
    double drop_altitude_;
    double search_speed_;
};

} // namespace common

#endif // COMMON_CONFIG_H
