#include "mavlink/node.h"

#include <cstring>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>


namespace mavlink {

/* ================= CONSTRUCTOR ================= */

// MavlinkNode::MavlinkNode(uint8_t system_id, uint8_t component_id)
//     : system_id_(system_id),
//       component_id_(component_id),
//       sock_fd_(-1),
//       running_(true)
// {
//     sock_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
//     if (sock_fd_ < 0) {
//         perror("socket");
//         return;
//     }

//     /* ---- BIND (receive from MAVProxy) ---- */
//     sockaddr_in local{};
//     local.sin_family = AF_INET;
//     local.sin_addr.s_addr = INADDR_ANY;
//     local.sin_port = htons(14550);
//     // local.sin_port = htons(14550);

//     if (bind(sock_fd_, (sockaddr*)&local, sizeof(local)) < 0) {
//         perror("bind");
//         close(sock_fd_);
//         sock_fd_ = -1;
//         return;
//     }

//     /* ---- TARGET: MAVProxy INPUT ---- */
//     std::memset(&target_addr_, 0, sizeof(target_addr_));
//     target_addr_.sin_family = AF_INET;
//     // target_addr_.sin_port = htons(14550);
//     target_addr_.sin_port = htons(14560);
//     inet_pton(AF_INET, "127.0.0.1", &target_addr_.sin_addr);

//     /* ---- START RX THREAD ---- */
//     rx_thread_ = std::thread(&MavlinkNode::rxLoop, this);

//     std::cout << "[MAVLINK NODE] SYSID="
//               << int(system_id_)
//               << " COMPID="
//               << int(component_id_)
//               << std::endl;
// }

MavlinkNode::MavlinkNode(uint8_t system_id, uint8_t component_id)
    : system_id_(system_id),
      component_id_(component_id),
      sock_fd_(-1),
      running_(true)
{
    // ---- OPEN SERIAL DEVICE ----
    sock_fd_ = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC);
    if (sock_fd_ < 0) {
        perror("open(/dev/ttyACM0)");
        return;
    }

    // ---- CONFIGURE SERIAL PORT ----
    struct termios tty{};
    if (tcgetattr(sock_fd_, &tty) != 0) {
        perror("tcgetattr");
        close(sock_fd_);
        sock_fd_ = -1;
        return;
    }

    // Baud rate (required even for USB CDC)
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    // 8N1
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    // Raw mode
    tty.c_iflag = 0;
    tty.c_oflag = 0;
    tty.c_lflag = 0;

    // Read behavior
    tty.c_cc[VMIN]  = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(sock_fd_, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        close(sock_fd_);
        sock_fd_ = -1;
        return;
    }

    std::cout << "[MAVLINK NODE] Connected to FC via /dev/ttyACM0\n";

    // ---- START RX THREAD ----
    rx_thread_ = std::thread(&MavlinkNode::rxLoop, this);

    std::cout << "[MAVLINK NODE] SYSID="
              << int(system_id_)
              << " COMPID="
              << int(component_id_)
              << std::endl;
}



// MavlinkNode::~MavlinkNode()
// {
//     running_ = false;

//     if (rx_thread_.joinable()) {
//         rx_thread_.join();
//     }

//     if (sock_fd_ >= 0) {
//         close(sock_fd_);
//     }
// }

MavlinkNode::~MavlinkNode()
{
    running_ = false;

    if (rx_thread_.joinable()) {
        rx_thread_.join();
    }

    if (sock_fd_ >= 0) {
        close(sock_fd_);
        sock_fd_ = -1;
    }
}


/* ================= RECEIVE LOOP ================= */

// void MavlinkNode::rxLoop()
// {
//     uint8_t buffer[2048];
//     sockaddr_in src{};
//     socklen_t src_len = sizeof(src);

//     mavlink_message_t msg;
//     mavlink_status_t status;

//     while (running_) {
//         ssize_t n = recvfrom(
//             sock_fd_,
//             buffer,
//             sizeof(buffer),
//             MSG_DONTWAIT,
//             (sockaddr*)&src,
//             &src_len
//         );

//         if (n <= 0) {
//             usleep(1000); // 1ms
//             continue;
//         }

//         for (ssize_t i = 0; i < n; i++) {
//             if (mavlink_parse_char(
//                     MAVLINK_COMM_0,
//                     buffer[i],
//                     &msg,
//                     &status))
//             {
//                 handleMessage(msg);
//             }
//         }
//     }
// }
void MavlinkNode::rxLoop()
{
    uint8_t buffer[256];

    mavlink_message_t msg;
    mavlink_status_t status{};

    while (running_) {
        ssize_t n = read(sock_fd_, buffer, sizeof(buffer));

        if (n < 0) {
            if (errno == EINTR) {
                continue;
            }
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                usleep(1000);
                continue;
            }

            perror("read(/dev/ttyACM0)");
            usleep(1000);
            continue;
        }

        if (n == 0) {
            // No data available (normal for serial)
            usleep(1000);
            continue;
        }

        for (ssize_t i = 0; i < n; i++) {
            if (mavlink_parse_char(
                    MAVLINK_COMM_0,
                    buffer[i],
                    &msg,
                    &status))
            {
                handleMessage(msg);
            }
        }
    }
}


/* ================= MESSAGE HANDLER ================= */

void MavlinkNode::handleMessage(const mavlink_message_t& msg)
{
    switch (msg.msgid) {

    case MAVLINK_MSG_ID_HEARTBEAT:
        fc_alive_ = true;
        break;

    case MAVLINK_MSG_ID_STATUSTEXT:
        break;

    default:
        break;
    }
}

bool MavlinkNode::fcAlive() const {
    return fc_alive_.load();
}



/* ================= HEARTBEAT ================= */

void MavlinkNode::sendHeartbeat()
{
    if (sock_fd_ < 0) return;

    mavlink_message_t msg{};

    mavlink_msg_heartbeat_pack(
        system_id_,
        component_id_,
        &msg,
        MAV_TYPE_ONBOARD_CONTROLLER,
        MAV_AUTOPILOT_INVALID,
        0,
        0,
        MAV_STATE_ACTIVE
    );

    sendRawMessage(msg);

    printf("Sent heartbeat from SYSID=%d COMPID=%d\n",
       system_id_, component_id_);

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
        0,
        0
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
        1,   // target system (AUTOPILOT)
        1,   // target component
        MAV_CMD_DO_SET_SERVO,
        0,
        channel,
        pwm,
        0, 0, 0, 0, 0
    );

    sendRawMessage(msg);
}

/* ================= LOW LEVEL SEND ================= */

// void MavlinkNode::sendRawMessage(const mavlink_message_t& msg)
// {
//     if (sock_fd_ < 0) return;

//     uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
//     uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

//     ssize_t sent = sendto(
//         sock_fd_,
//         buffer,
//         len,
//         0,
//         reinterpret_cast<sockaddr*>(&target_addr_),
//         sizeof(target_addr_)
//     );

//     if (sent < 0) {
//         perror("sendto");
//     }
// }

// } // namespace mavlink

void MavlinkNode::sendRawMessage(const mavlink_message_t& msg)
{
    if (sock_fd_ < 0) return;

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

    ssize_t n = write(sock_fd_, buffer, len);

    if (n < 0) {
        if (errno == EINTR) return;
        perror("write(/dev/ttyACM0)");
    }
}


}
