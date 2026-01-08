#ifndef MAVLINK_SERVO_CONTROLLER_H
#define MAVLINK_SERVO_CONTROLLER_H

namespace mavlink {

class ServoController {
public:
    ServoController();
    ~ServoController();

    // Initialize servo controller
    bool initialize();
    
    // Set servo position (0-1000 range)
    bool setServoPosition(int servo_id, int position);
    
    // Trigger drop mechanism
    bool triggerDrop();
    
    // Reset servo to initial position
    bool resetServo(int servo_id);
    
    // Get current servo position
    int getServoPosition(int servo_id) const;

private:
    static const int MAX_SERVOS = 8;
    int servo_positions_[MAX_SERVOS];
};

} // namespace mavlink

#endif // MAVLINK_SERVO_CONTROLLER_H
