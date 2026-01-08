#include "mavlink/status_reporter.h"
#include <iostream>
#include <chrono>

namespace mavlink {

StatusReporter::StatusReporter() 
    : last_report_time_(0.0) {
}

StatusReporter::~StatusReporter() {
}

void StatusReporter::initialize() {
    // Stub implementation
    std::cout << "Initializing status reporter" << std::endl;
    last_report_time_ = 0.0;
}

void StatusReporter::reportStatus(common::SystemStatus status) {
    // Stub implementation
    std::cout << "Reporting system status: " << static_cast<int>(status) << std::endl;
    
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    last_report_time_ = std::chrono::duration<double>(duration).count();
}

void StatusReporter::reportPosition(const common::Position& pos) {
    // Stub implementation
    std::cout << "Reporting position: lat=" << pos.latitude 
              << ", lon=" << pos.longitude 
              << ", alt=" << pos.altitude << std::endl;
    
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    last_report_time_ = std::chrono::duration<double>(duration).count();
}

void StatusReporter::reportMissionProgress(int progress_percent) {
    // Stub implementation
    std::cout << "Mission progress: " << progress_percent << "%" << std::endl;
    
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    last_report_time_ = std::chrono::duration<double>(duration).count();
}

double StatusReporter::getLastReportTime() const {
    return last_report_time_;
}

} // namespace mavlink
