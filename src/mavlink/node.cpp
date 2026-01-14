#include "mavlink/node.h"

#include <cstring>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

namespace mavlink {

/* ================= CONSTRUCTOR ================= */

MavlinkNode::MavlinkNode(uint8_t system_id, uint8_t component_id)
    : system_id_(system_id),
      component_id_(component_id) {

    sock_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd_ < 0) {
        perror("socket");
        return;
    }

    std::memset(&target_addr_, 0, sizeof(target_addr_));
    target_addr_.sin_family = AF_INET;
    target_addr_.sin_port   = htons(6669);                  // MAVProxy --out port
    inet_pton(AF_INET, "100.123.232.102", &target_addr_.sin_addr);
}

MavlinkNode::~MavlinkNode() {
    if (sock_fd_ >= 0) {
        close(sock_fd_);
    }
}

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
        0,  // id
        0   // chunk_seq
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
        0,  // target system (broadcast)
        0,  // target component
        MAV_CMD_DO_SET_SERVO,
        0,
        static_cast<float>(channel),
        static_cast<float>(pwm),
        0, 0, 0, 0, 0
    );

    sendRawMessage(msg);
}

/* ================= LOW LEVEL SEND ================= */

void MavlinkNode::sendRawMessage(const mavlink_message_t& msg) {
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
