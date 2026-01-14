#ifndef MAVLINK_STATUS_REPORTER_H
#define MAVLINK_STATUS_REPORTER_H

#include <string>
#include <cstdint>

namespace mavlink {

class MavlinkNode;  // forward declaration

class StatusReporter {
public:
    explicit StatusReporter(MavlinkNode& mavlink);

    // Send plain text to GCS
    bool send(const std::string& text,
              uint8_t severity = 6); // MAV_SEVERITY_INFO

private:
    MavlinkNode& mavlink_;
};

} // namespace mavlink

#endif // MAVLINK_STATUS_REPORTER_H
