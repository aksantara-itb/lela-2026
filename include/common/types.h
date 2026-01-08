#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <cstdint>

namespace common {

// Common data types used across modules
struct Position {
    double latitude;
    double longitude;
    double altitude;
};

struct Velocity {
    double vx;
    double vy;
    double vz;
};

struct Attitude {
    double roll;
    double pitch;
    double yaw;
};

enum class SystemStatus {
    IDLE,
    ARMED,
    SEARCHING,
    DROPPING,
    ERROR
};

} // namespace common

#endif // COMMON_TYPES_H
