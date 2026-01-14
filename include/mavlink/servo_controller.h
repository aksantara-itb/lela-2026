#ifndef MAVLINK_SERVO_CONTROLLER_H
#define MAVLINK_SERVO_CONTROLLER_H

#include <cstdint>

namespace mavlink {

class MavlinkNode;  // forward declaration

class ServoController {
public:
    explicit ServoController(MavlinkNode& mavlink);

    // Open drop servo
    bool open();

    // Close drop servo
    bool close();

    // Get last commanded state
    bool isOpen() const;

private:
    MavlinkNode& mavlink_;

    bool is_open_{false};

    // Configurable via config.h
    uint8_t servo_channel_;
    uint16_t pwm_open_;
    uint16_t pwm_close_;
};

} // namespace mavlink

#endif // MAVLINK_SERVO_CONTROLLER_H
