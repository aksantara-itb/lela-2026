#ifndef VISION_CAMERA_INTERFACE_H
#define VISION_CAMERA_INTERFACE_H

#include <string>
#include <vector>
#include <cstdint>

namespace vision {

struct Frame {
    int width;
    int height;
    int channels;
    std::vector<uint8_t> data;
};

class CameraInterface {
public:
    CameraInterface();
    ~CameraInterface();

    // Initialize camera
    bool initialize(const std::string& device_path);
    
    // Start/stop capture
    bool startCapture();
    bool stopCapture();
    
    // Get next frame (blocking)
    bool getFrame(Frame& frame);
    
    // Check if camera is open
    bool isOpen() const;
    
    // Get camera properties
    int getWidth() const;
    int getHeight() const;
    int getFPS() const;

private:
    std::string device_path_;
    bool is_open_;
    int width_;
    int height_;
    int fps_;
};

} // namespace vision

#endif // VISION_CAMERA_INTERFACE_H
