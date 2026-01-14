#include "mavlink/node.h"

#include <cstring>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

namespace mavlink {

/* ================= CONSTRUCTOR ================= */

MavlinkNode::MavlinkNode(uint8_t system_id, uint8_t component_id)
    : system_id_(system_id),
      component_id_(component_id),
      sock_fd_(-1)
{
    sock_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd_ < 0) {
        perror("socket");
        return;
    }

    /* ---- BIND (receive from MAVProxy) ---- */
    sockaddr_in local{};
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;
    local.sin_port = htons(14551);   // MAVProxy --out

    if (bind(sock_fd_, (sockaddr*)&local, sizeof(local)) < 0) {
        perror("bind");
        close(sock_fd_);
        sock_fd_ = -1;
        return;
    }

    /* ---- TARGET: MAVProxy INPUT ---- */
    std::memset(&target_addr_, 0, sizeof(target_addr_));
    target_addr_.sin_family = AF_INET;
    target_addr_.sin_port   = htons(14550);  // MAVProxy master input
    inet_pton(AF_INET, "127.0.0.1", &target_addr_.sin_addr);    

    std::cout << "[MAVLINK NODE] SYSID="
              << int(system_id_)
              << " COMPID="
              << int(component_id_)
              << std::endl;
}

MavlinkNode::~MavlinkNode() {
    if (sock_fd_ >= 0) {
        close(sock_fd_);
    }
}

/* ================= HEARTBEAT ================= */

void MavlinkNode::sendHeartbeat()
{
    if (sock_fd_ < 0) return;

    mavlink_message_t msg{};

    mavlink_msg_heartbeat_pack(
        system_id_,                    // source system
        component_id_,                 // source component
        &msg,
        MAV_TYPE_ONBOARD_CONTROLLER,   // component type
        MAV_AUTOPILOT_INVALID,         // not an autopilot
        0,                             // base mode
        0,                             // custom mode
        MAV_STATE_ACTIVE
    );

    sendRawMessage(msg);
}

/* ================= STATUSTEXT ================= */

void MavlinkNode::sendStatusText(uint8_t severity,
                                 const std::string& text)
{
    mavlink_message_t msg{};
    char text_buf[MAVLINK_MSG_STATUSTEXT_FIELD_TEXT_LEN]{};

    std::strncpy(
        text_buf,
        text.c_str(),
        MAVLINK_MSG_STATUSTEXT_FIELD_TEXT_LEN - 1
    );

    mavlink_msg_statustext_pack(
        system_id_,
        component_id_,
        &msg,
        severity,
        text_buf,
        0,  // id
        0   // chunk_seq
    );

    sendRawMessage(msg);
}

/* ================= SERVO ================= */

void MavlinkNode::sendServoCommand(uint8_t channel, uint16_t pwm)
{
    mavlink_message_t msg{};

    mavlink_msg_command_long_pack(
        system_id_,
        component_id_,
        &msg,
        0,   // target system (broadcast)
        0,   // target component
        MAV_CMD_DO_SET_SERVO,
        0,
        channel,
        pwm,
        0, 0, 0, 0, 0
    );

    sendRawMessage(msg);
}

/* ================= LOW LEVEL SEND ================= */

void MavlinkNode::sendRawMessage(const mavlink_message_t& msg)
{
    if (sock_fd_ < 0) return;

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

    ssize_t sent = sendto(
        sock_fd_,
        buffer,
        len,
        0,
        reinterpret_cast<sockaddr*>(&target_addr_),
        sizeof(target_addr_)
    );

    if (sent < 0) {
        perror("sendto");
    }
}

} // namespace mavlink
