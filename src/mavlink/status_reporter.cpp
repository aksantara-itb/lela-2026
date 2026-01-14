#include "mavlink/status_reporter.h"
#include "mavlink/node.h"

namespace mavlink {

StatusReporter::StatusReporter(MavlinkNode& mavlink)
    : mavlink_(mavlink) {}

/* ================= SEND ================= */

bool StatusReporter::send(const std::string& text, uint8_t severity) {
    mavlink_.sendStatusText(severity, text);
    return true;
}

} // namespace mavlink
