#include "common/state.h"

namespace common {

SharedState& SharedState::getInstance() {
    static SharedState instance;
    return instance;
}

SharedState::SharedState() 
    : position_{0.0, 0.0, 0.0},
      attitude_{0.0, 0.0, 0.0},
      velocity_{0.0, 0.0, 0.0},
      system_status_(SystemStatus::IDLE),
      target_detected_(false) {
}

SharedState::~SharedState() {
}

void SharedState::setPosition(const Position& pos) {
    std::lock_guard<std::mutex> lock(mutex_);
    position_ = pos;
}

Position SharedState::getPosition() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return position_;
}

void SharedState::setAttitude(const Attitude& att) {
    std::lock_guard<std::mutex> lock(mutex_);
    attitude_ = att;
}

Attitude SharedState::getAttitude() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return attitude_;
}

void SharedState::setVelocity(const Velocity& vel) {
    std::lock_guard<std::mutex> lock(mutex_);
    velocity_ = vel;
}

Velocity SharedState::getVelocity() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return velocity_;
}

void SharedState::setSystemStatus(SystemStatus status) {
    std::lock_guard<std::mutex> lock(mutex_);
    system_status_ = status;
}

SystemStatus SharedState::getSystemStatus() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return system_status_;
}

void SharedState::setTargetDetected(bool detected) {
    std::lock_guard<std::mutex> lock(mutex_);
    target_detected_ = detected;
}

bool SharedState::isTargetDetected() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return target_detected_;
}

} // namespace common
