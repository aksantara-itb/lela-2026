#ifndef MISSION_MISSION_CONTROLLER_H
#define MISSION_MISSION_CONTROLLER_H

#include "common/types.h"
#include <string>

namespace mission {

enum class MissionState {
    IDLE,
    INIT,
    SEARCH,
    ALIGN,
    DROP,
    RETURN,
    COMPLETED,
    ERROR
};

class MissionController {
public:
    MissionController();
    ~MissionController();

    // Initialize mission controller
    bool initialize();
    
    // Start mission
    bool startMission();
    
    // Stop mission
    void stopMission();
    
    // Update mission state (called in main loop)
    void update();
    
    // Get current mission state
    MissionState getState() const;
    
    // Get mission progress
    int getProgressPercent() const;
    
    // Set mission parameters
    void setSearchArea(double lat_min, double lat_max, double lon_min, double lon_max);
    void setDropTarget(const common::Position& target);

private:
    void handleIdleState();
    void handleInitState();
    void handleSearchState();
    void handleAlignState();
    void handleDropState();
    void handleReturnState();
    
    MissionState state_;
    int progress_percent_;
    common::Position drop_target_;
    double search_lat_min_, search_lat_max_;
    double search_lon_min_, search_lon_max_;
    bool mission_running_;
};

} // namespace mission

#endif // MISSION_MISSION_CONTROLLER_H
