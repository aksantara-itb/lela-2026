#ifndef MAVLINK_NODE_H
#define MAVLINK_NODE_H

#include <cstdint>
#include <string>
#include <thread>
#include <atomic>

/* POSIX sockets */
#include <netinet/in.h>

/* MAVLink core */
extern "C" {
#include "../../third_party/mavlink/common/mavlink.h"
}

namespace mavlink {

class MavlinkNode {
public:
    MavlinkNode(uint8_t system_id = 255,
                uint8_t component_id = MAV_COMP_ID_ONBOARD_COMPUTER);

    ~MavlinkNode();

    /* ================= HEARTBEAT ================= */
    void sendHeartbeat();

    /* ================= STATUSTEXT ================= */
    void sendStatusText(uint8_t severity, const std::string& text);

    /* ================= SERVO ================= */
    void sendServoCommand(uint8_t channel, uint16_t pwm);

    /* ================= VFR_HUD ================= */
    void acceptVfrHud(const mavlink_message_t& msg);

    /* ================= MISSION ================= */
    void acceptMissionReached(const mavlink_message_t& msg);

    bool fcAlive() const;

private:
    /* ================= RX ================= */
    void rxLoop();
    void handleMessage(const mavlink_message_t& msg);

    /* ================= TX ================= */
    void sendRawMessage(const mavlink_message_t& msg);

    uint8_t system_id_;
    uint8_t component_id_;

    /* UDP transport */
    int sock_fd_;
    sockaddr_in target_addr_;

    /* RX thread control */
    std::thread rx_thread_;
    std::atomic<bool> running_;

    std::atomic<bool> fc_alive_{false};
};

} // namespace mavlink

#endif // MAVLINK_NODE_H
