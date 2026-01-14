#include "mavlink/servo_controller.h"
#include "mavlink/node.h"

namespace mavlink {

ServoController::ServoController(MavlinkNode& mavlink)
    : mavlink_(mavlink)
{
    // These are expected to be set via config.h or externally
    // Leaving them uninitialized here is intentional per design
}

/* ================= OPEN ================= */

bool ServoController::open() {
    mavlink_.sendServoCommand(servo_channel_, pwm_open_);
    is_open_ = true;
    return true;
}

/* ================= CLOSE ================= */

bool ServoController::close() {
    mavlink_.sendServoCommand(servo_channel_, pwm_close_);
    is_open_ = false;
    return true;
}

/* ================= STATE ================= */

bool ServoController::isOpen() const {
    return is_open_;
}

} // namespace mavlink
