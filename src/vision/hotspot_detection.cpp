#include "vision/hotspot_detection.h"
#include "common/state.h"
#include <iostream>
#include <algorithm>
#include <cmath>

namespace vision {

HotspotDetection::HotspotDetection() 
    : h_min_(0), h_max_(180),
      s_min_(0), s_max_(255),
      v_min_(0), v_max_(255),
      initialized_(false) {
}

HotspotDetection::~HotspotDetection() {
}

void HotspotDetection::initialize() {
    // Stub implementation - set default color range for red
    setColorRange(0, 10, 100, 255, 100, 255);
    initialized_ = true;
    std::cout << "Initializing hotspot detection" << std::endl;
}

void HotspotDetection::setColorRange(int h_min, int h_max, int s_min, int s_max, int v_min, int v_max) {
    h_min_ = h_min;
    h_max_ = h_max;
    s_min_ = s_min;
    s_max_ = s_max;
    v_min_ = v_min;
    v_max_ = v_max;
    
    std::cout << "Color range set: H[" << h_min << "-" << h_max << "], "
              << "S[" << s_min << "-" << s_max << "], "
              << "V[" << v_min << "-" << v_max << "]" << std::endl;
}

bool HotspotDetection::detectHotspots(const Frame& frame, std::vector<Hotspot>& hotspots) {
    if (!initialized_) {
        std::cout << "Hotspot detection not initialized" << std::endl;
        return false;
    }
    
    // Stub implementation - return dummy hotspot
    hotspots.clear();
    
    Hotspot dummy;
    dummy.x = frame.width / 2 - 50;
    dummy.y = frame.height / 2 - 50;
    dummy.width = 100;
    dummy.height = 100;
    dummy.confidence = 0.85;
    
    hotspots.push_back(dummy);
    
    std::cout << "Detected " << hotspots.size() << " hotspot(s)" << std::endl;
    return true;
}

bool HotspotDetection::getBestHotspot(const std::vector<Hotspot>& hotspots, Hotspot& best) {
    if (hotspots.empty()) {
        return false;
    }
    
    // Find hotspot with highest confidence
    auto it = std::max_element(hotspots.begin(), hotspots.end(),
        [](const Hotspot& a, const Hotspot& b) {
            return a.confidence < b.confidence;
        });
    
    best = *it;
    return true;
}

bool HotspotDetection::isHotspotCentered(const Hotspot& hotspot, const Frame& frame, double threshold) {
    int center_x = hotspot.x + hotspot.width / 2;
    int center_y = hotspot.y + hotspot.height / 2;
    
    int frame_center_x = frame.width / 2;
    int frame_center_y = frame.height / 2;
    
    double dx = static_cast<double>(center_x - frame_center_x) / frame.width;
    double dy = static_cast<double>(center_y - frame_center_y) / frame.height;
    
    double distance = std::sqrt(dx * dx + dy * dy);
    
    return distance < threshold;
}

} // namespace vision
