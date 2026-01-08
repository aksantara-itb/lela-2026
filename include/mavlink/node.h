#ifndef MAVLINK_NODE_H
#define MAVLINK_NODE_H

#include <string>
#include <thread>
#include <atomic>

namespace mavlink {

class MavlinkNode {
public:
    MavlinkNode();
    ~MavlinkNode();

    // Initialize and connect to MAVLink
    bool initialize(const std::string& connection_url, int port);
    
    // Start/stop MAVLink I/O
    void start();
    void stop();
    
    // Send command to vehicle
    bool sendCommand(int command_id);
    
    // Check if connected
    bool isConnected() const;

private:
    void receiveThread();
    void sendThread();
    
    std::thread receive_thread_;
    std::thread send_thread_;
    std::atomic<bool> running_;
    std::atomic<bool> connected_;
    int port_;
    std::string connection_url_;
};

} // namespace mavlink

#endif // MAVLINK_NODE_H
