#include "../../include/common/state.h"

namespace common {

SharedState::SharedState()
    : position_{},
      attitude_{},
      velocity_{},
      system_status_{SystemStatus::IDLE},
      target_detected_{false}
{
}

SharedState::~SharedState() = default;

SharedState& SharedState::getInstance() {
    static SharedState instance;
    return instance;
}

/* -------------------- Position -------------------- */

void SharedState::setPosition(const Position& pos) {
    std::lock_guard<std::mutex> lock(mutex_);
    position_ = pos;
}

Position SharedState::getPosition() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return position_;
}

/* -------------------- Attitude -------------------- */

void SharedState::setAttitude(const Attitude& att) {
    std::lock_guard<std::mutex> lock(mutex_);
    attitude_ = att;
}

Attitude SharedState::getAttitude() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return attitude_;
}

/* -------------------- Velocity -------------------- */

void SharedState::setVelocity(const Velocity& vel) {
    std::lock_guard<std::mutex> lock(mutex_);
    velocity_ = vel;
}

Velocity SharedState::getVelocity() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return velocity_;
}

/* -------------------- System Status -------------------- */

void SharedState::setSystemStatus(SystemStatus status) {
    std::lock_guard<std::mutex> lock(mutex_);
    system_status_ = status;
}

SystemStatus SharedState::getSystemStatus() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return system_status_;
}

/* -------------------- Target -------------------- */

void SharedState::setTargetDetected(bool detected) {
    std::lock_guard<std::mutex> lock(mutex_);
    target_detected_ = detected;
}

bool SharedState::isTargetDetected() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return target_detected_;
}

} // namespace common
