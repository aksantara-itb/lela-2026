#include "mission/mission_controller.h"
#include "common/state.h"
#include <iostream>

namespace mission {

MissionController::MissionController() 
    : state_(MissionState::IDLE),
      progress_percent_(0),
      drop_target_{0.0, 0.0, 0.0},
      search_lat_min_(0.0), search_lat_max_(0.0),
      search_lon_min_(0.0), search_lon_max_(0.0),
      mission_running_(false) {
}

MissionController::~MissionController() {
    stopMission();
}

bool MissionController::initialize() {
    // Stub implementation
    std::cout << "Initializing mission controller" << std::endl;
    state_ = MissionState::IDLE;
    progress_percent_ = 0;
    return true;
}

bool MissionController::startMission() {
    if (mission_running_) {
        std::cout << "Mission already running" << std::endl;
        return false;
    }
    
    // Stub implementation
    std::cout << "Starting mission" << std::endl;
    mission_running_ = true;
    state_ = MissionState::INIT;
    progress_percent_ = 0;
    
    common::SharedState::getInstance().setSystemStatus(common::SystemStatus::ARMED);
    return true;
}

void MissionController::stopMission() {
    if (!mission_running_) {
        return;
    }
    
    // Stub implementation
    std::cout << "Stopping mission" << std::endl;
    mission_running_ = false;
    state_ = MissionState::IDLE;
    
    common::SharedState::getInstance().setSystemStatus(common::SystemStatus::IDLE);
}

void MissionController::update() {
    if (!mission_running_) {
        return;
    }
    
    // State machine update
    switch (state_) {
        case MissionState::IDLE:
            handleIdleState();
            break;
        case MissionState::INIT:
            handleInitState();
            break;
        case MissionState::SEARCH:
            handleSearchState();
            break;
        case MissionState::ALIGN:
            handleAlignState();
            break;
        case MissionState::DROP:
            handleDropState();
            break;
        case MissionState::RETURN:
            handleReturnState();
            break;
        case MissionState::COMPLETED:
        case MissionState::ERROR:
            // Terminal states
            break;
    }
}

MissionState MissionController::getState() const {
    return state_;
}

int MissionController::getProgressPercent() const {
    return progress_percent_;
}

void MissionController::setSearchArea(double lat_min, double lat_max, double lon_min, double lon_max) {
    search_lat_min_ = lat_min;
    search_lat_max_ = lat_max;
    search_lon_min_ = lon_min;
    search_lon_max_ = lon_max;
    
    std::cout << "Search area set: lat[" << lat_min << "-" << lat_max << "], "
              << "lon[" << lon_min << "-" << lon_max << "]" << std::endl;
}

void MissionController::setDropTarget(const common::Position& target) {
    drop_target_ = target;
    std::cout << "Drop target set: " << target.latitude << ", " << target.longitude << std::endl;
}

void MissionController::handleIdleState() {
    // Stub implementation
}

void MissionController::handleInitState() {
    // Stub implementation - transition to search
    std::cout << "Mission state: INIT -> SEARCH" << std::endl;
    state_ = MissionState::SEARCH;
    progress_percent_ = 10;
    common::SharedState::getInstance().setSystemStatus(common::SystemStatus::SEARCHING);
}

void MissionController::handleSearchState() {
    // Stub implementation - check for target detection
    common::SharedState& state = common::SharedState::getInstance();
    
    if (state.isTargetDetected()) {
        std::cout << "Mission state: SEARCH -> ALIGN" << std::endl;
        state_ = MissionState::ALIGN;
        progress_percent_ = 50;
    }
}

void MissionController::handleAlignState() {
    // Stub implementation - align with target
    std::cout << "Mission state: ALIGN -> DROP" << std::endl;
    state_ = MissionState::DROP;
    progress_percent_ = 75;
    common::SharedState::getInstance().setSystemStatus(common::SystemStatus::DROPPING);
}

void MissionController::handleDropState() {
    // Stub implementation - execute drop
    std::cout << "Mission state: DROP -> RETURN" << std::endl;
    state_ = MissionState::RETURN;
    progress_percent_ = 90;
}

void MissionController::handleReturnState() {
    // Stub implementation - return to home
    std::cout << "Mission state: RETURN -> COMPLETED" << std::endl;
    state_ = MissionState::COMPLETED;
    progress_percent_ = 100;
    mission_running_ = false;
    common::SharedState::getInstance().setSystemStatus(common::SystemStatus::IDLE);
}

} // namespace mission
