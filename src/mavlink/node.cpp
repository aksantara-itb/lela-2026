#include "mavlink/node.h"

#include <cstring>
#include <iostream>

namespace mavlink {

/* ================= CONSTRUCTOR ================= */

MavlinkNode::MavlinkNode(uint8_t system_id, uint8_t component_id)
    : system_id_(system_id),
      component_id_(component_id) {}

/* ================= STATUSTEXT ================= */

void MavlinkNode::sendStatusText(uint8_t severity, const std::string& text) {
    mavlink_message_t msg;
    char buffer[MAVLINK_MSG_STATUSTEXT_FIELD_TEXT_LEN] = {};

    std::strncpy(buffer, text.c_str(),
                 MAVLINK_MSG_STATUSTEXT_FIELD_TEXT_LEN - 1);

    mavlink_msg_statustext_pack(
        system_id_,
        component_id_,
        &msg,
        severity,
        buffer,
        0,  // id (0 = no grouping)
        0   // chunk_seq (0 = single message)
    );


    sendRawMessage(msg);
}

/* ================= SERVO ================= */

void MavlinkNode::sendServoCommand(uint8_t channel, uint16_t pwm) {
    mavlink_message_t msg;

    mavlink_msg_command_long_pack(
        system_id_,
        component_id_,
        &msg,
        0,                          // target system
        0,                          // target component
        MAV_CMD_DO_SET_SERVO,
        0,                          // confirmation
        static_cast<float>(channel), // param1: servo number
        static_cast<float>(pwm),     // param2: PWM
        0.0f,                        // param3
        0.0f,                        // param4
        0.0f,                        // param5
        0.0f,                        // param6
        0.0f                         // param7
    );


    sendRawMessage(msg);
}

/* ================= VFR_HUD ================= */

void MavlinkNode::acceptVfrHud(const mavlink_message_t& msg) {
    if (msg.msgid != MAVLINK_MSG_ID_VFR_HUD) {
        return;
    }

    mavlink_vfr_hud_t hud;
    mavlink_msg_vfr_hud_decode(&msg, &hud);

    // Example usage / debug (safe to remove)
    std::cout << "[VFR_HUD] "
              << "AS=" << hud.airspeed
              << " GS=" << hud.groundspeed
              << " HDG=" << hud.heading
              << " THR=" << hud.throttle
              << " ALT=" << hud.alt
              << " CLB=" << hud.climb
              << std::endl;
}

/* ================= MISSION ================= */

void MavlinkNode::acceptMissionReached(const mavlink_message_t& msg) {
    if (msg.msgid != MAVLINK_MSG_ID_MISSION_ITEM_REACHED) {
        return;
    }

    mavlink_mission_item_reached_t reached;
    mavlink_msg_mission_item_reached_decode(&msg, &reached);

    // Example usage / debug (safe to remove)
    std::cout << "[MISSION] Waypoint reached: "
              << reached.seq
              << std::endl;
}

/* ================= LOW LEVEL SEND ================= */
void MavlinkNode::sendRawMessage(const mavlink_message_t& msg) {
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    const uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

    std::cout << "MAVLink TX (" << len << " bytes): ";
    for (uint16_t i = 0; i < len; ++i) {
        printf("%02X ", buffer[i]);
    }
    std::cout << std::endl;
}

} // namespace mavlink
