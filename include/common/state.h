#ifndef COMMON_STATE_H
#define COMMON_STATE_H

#include "types.h"
#include <mutex>

namespace common {

class SharedState {
public:
    static SharedState& getInstance();
    
    // Position and attitude accessors
    void setPosition(const Position& pos);
    Position getPosition() const;
    
    void setAttitude(const Attitude& att);
    Attitude getAttitude() const;
    
    void setVelocity(const Velocity& vel);
    Velocity getVelocity() const;
    
    // System status
    void setSystemStatus(SystemStatus status);
    SystemStatus getSystemStatus() const;
    
    // Target information
    void setTargetDetected(bool detected);
    bool isTargetDetected() const;

private:
    SharedState();
    ~SharedState();
    SharedState(const SharedState&) = delete;
    SharedState& operator=(const SharedState&) = delete;
    
    mutable std::mutex mutex_;
    Position position_;
    Attitude attitude_;
    Velocity velocity_;
    SystemStatus system_status_;
    bool target_detected_;
};

} // namespace common

#endif // COMMON_STATE_H
