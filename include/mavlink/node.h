// #ifndef MAVLINK_NODE_H
// #define MAVLINK_NODE_H

// #include <string>
// #include <thread>
// #include <atomic>

// namespace mavlink {

// class MavlinkNode {
// public:
//     MavlinkNode();
//     ~MavlinkNode();

//     // Initialize and connect to MAVLink
//     bool initialize(const std::string& connection_url, int port);
    
//     // Start/stop MAVLink I/O
//     void start();
//     void stop();
    
//     // Send command to vehicle
//     bool sendCommand(int command_id);
    
//     // Check if connected
//     bool isConnected() const;

// private:
//     void receiveThread();
//     void sendThread();
    
//     std::thread receive_thread_;
//     std::thread send_thread_;
//     std::atomic<bool> running_;
//     std::atomic<bool> connected_;
//     int port_;
//     std::string connection_url_;
// };

// } // namespace mavlink

// #endif // MAVLINK_NODE_H

#ifndef MAVLINK_NODE_H
#define MAVLINK_NODE_H

#include <string>
#include <thread>
#include <atomic>
#include <cstdint>

namespace mavlink {

class MavlinkNode {
public:
    MavlinkNode();
    ~MavlinkNode();

    // Initialize and connect to MAVLink (UDP / Serial handled internally)
    bool initialize(const std::string& connection_url, int port);

    // Start/stop MAVLink I/O threads
    void start();
    void stop();

    // Connection state
    bool isConnected() const;

    /* ================= SAFE, ALLOWED ACTIONS ================= */

    // Send STATUSTEXT to GCS
    bool sendStatusText(const std::string& text,
                        uint8_t severity = 6); // MAV_SEVERITY_INFO

    // Move a servo using MAV_CMD_DO_SET_SERVO
    bool setServo(uint8_t servo_number, uint16_t pwm);

private:
    /* ================= INTERNAL THREADS ================= */

    void receiveThread();
    void sendThread();

    /* ================= INTERNAL STATE ================= */

    std::thread receive_thread_;
    std::thread send_thread_;

    std::atomic<bool> running_{false};
    std::atomic<bool> connected_{false};

    int port_{0};
    std::string connection_url_;

    /* ================= MAVLINK IDS ================= */

    uint8_t system_id_{255};     // Companion computer
    uint8_t component_id_{190};  // MAV_COMP_ID_ONBOARD_COMPUTER
};

} // namespace mavlink

#endif // MAVLINK_NODE_H
