#ifndef MAVLINK_STATUS_REPORTER_H
#define MAVLINK_STATUS_REPORTER_H

#include "common/types.h"
#include <string>

namespace mavlink {

class StatusReporter {
public:
    StatusReporter();
    ~StatusReporter();

    // Initialize status reporter
    void initialize();
    
    // Report system status
    void reportStatus(common::SystemStatus status);
    
    // Report position
    void reportPosition(const common::Position& pos);
    
    // Report mission progress
    void reportMissionProgress(int progress_percent);
    
    // Get last status report time
    double getLastReportTime() const;

private:
    double last_report_time_;
};

} // namespace mavlink

#endif // MAVLINK_STATUS_REPORTER_H
