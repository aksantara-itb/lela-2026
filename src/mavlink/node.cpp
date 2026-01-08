#include "mavlink/node.h"
#include "common/state.h"
#include <iostream>
#include <chrono>
#include <thread>

namespace mavlink {

MavlinkNode::MavlinkNode() 
    : running_(false), 
      connected_(false), 
      port_(0) {
}

MavlinkNode::~MavlinkNode() {
    stop();
}

bool MavlinkNode::initialize(const std::string& connection_url, int port) {
    connection_url_ = connection_url;
    port_ = port;
    
    // Stub implementation
    std::cout << "Initializing MAVLink node: " << connection_url << ":" << port << std::endl;
    connected_ = true;
    return true;
}

void MavlinkNode::start() {
    if (running_) return;
    
    running_ = true;
    receive_thread_ = std::thread(&MavlinkNode::receiveThread, this);
    send_thread_ = std::thread(&MavlinkNode::sendThread, this);
    
    std::cout << "MAVLink node started" << std::endl;
}

void MavlinkNode::stop() {
    if (!running_) return;
    
    running_ = false;
    
    if (receive_thread_.joinable()) {
        receive_thread_.join();
    }
    if (send_thread_.joinable()) {
        send_thread_.join();
    }
    
    std::cout << "MAVLink node stopped" << std::endl;
}

bool MavlinkNode::sendCommand(int command_id) {
    // Stub implementation
    std::cout << "Sending MAVLink command: " << command_id << std::endl;
    return true;
}

bool MavlinkNode::isConnected() const {
    return connected_;
}

void MavlinkNode::receiveThread() {
    // Stub implementation - would receive MAVLink messages
    while (running_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void MavlinkNode::sendThread() {
    // Stub implementation - would send MAVLink messages
    while (running_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

} // namespace mavlink
