#ifndef MAVLINK_NODE_H
#define MAVLINK_NODE_H

#include <cstdint>
#include <string>

/* MAVLink core */
extern "C" {
#include "../../third_party/mavlink/common/mavlink.h"
}

namespace mavlink {

/**
 * @brief Minimal MAVLink message sender (no transport).
 *
 * Responsibilities:
 *  - Build and send MAVLink messages
 *  - Accept MAVLink telemetry and mission state
 *
 * NOT responsible for:
 *  - Connection / sockets / UART
 *  - Threading
 */
class MavlinkNode {
public:
    MavlinkNode(uint8_t system_id = 255,
                uint8_t component_id = MAV_COMP_ID_ONBOARD_COMPUTER);

    /* ================= STATUSTEXT ================= */

    void sendStatusText(uint8_t severity, const std::string& text);

    /* ================= SERVO ================= */

    void sendServoCommand(uint8_t channel, uint16_t pwm);

    /* ================= VFR_HUD ================= */

    /**
     * @brief Accept incoming MAVLink VFR_HUD message
     */
    void acceptVfrHud(const mavlink_message_t& msg);


    /* ================= MISSION ================= */

    /**
     * @brief Accept MAVLink MISSION_ITEM_REACHED message
     *
     * Corresponds to /mavros/mission/reached
     */
    void acceptMissionReached(const mavlink_message_t& msg);

private:
    /* ================= LOW LEVEL SEND ================= */

    /**
     * @brief Send encoded MAVLink message bytes
     * @note Implemented by transport layer
     */
    void sendRawMessage(const mavlink_message_t& msg);

    uint8_t system_id_;
    uint8_t component_id_;
};

} // namespace mavlink

#endif // MAVLINK_NODE_H
