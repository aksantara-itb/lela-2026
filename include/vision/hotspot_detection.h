#ifndef VISION_HOTSPOT_DETECTION_H
#define VISION_HOTSPOT_DETECTION_H

#include "camera_interface.h"
#include "common/types.h"
#include <vector>

namespace vision {

struct Hotspot {
    int x;
    int y;
    int width;
    int height;
    double confidence;
};

class HotspotDetection {
public:
    HotspotDetection();
    ~HotspotDetection();

    // Initialize detector with color parameters
    void initialize();
    
    // Set target color range for detection (HSV)
    void setColorRange(int h_min, int h_max, int s_min, int s_max, int v_min, int v_max);
    
    // Detect hotspots in frame
    bool detectHotspots(const Frame& frame, std::vector<Hotspot>& hotspots);
    
    // Get the most confident hotspot
    bool getBestHotspot(const std::vector<Hotspot>& hotspots, Hotspot& best);
    
    // Check if hotspot is at center
    bool isHotspotCentered(const Hotspot& hotspot, const Frame& frame, double threshold = 0.1);

private:
    int h_min_, h_max_;
    int s_min_, s_max_;
    int v_min_, v_max_;
    bool initialized_;
};

} // namespace vision

#endif // VISION_HOTSPOT_DETECTION_H
