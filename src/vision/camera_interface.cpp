#include "vision/camera_interface.h"
#include <iostream>

namespace vision {

CameraInterface::CameraInterface() 
    : is_open_(false), 
      width_(640), 
      height_(480), 
      fps_(30) {
}

CameraInterface::~CameraInterface() {
    stopCapture();
}

bool CameraInterface::initialize(const std::string& device_path) {
    device_path_ = device_path;
    
    // Stub implementation
    std::cout << "Initializing camera: " << device_path << std::endl;
    is_open_ = true;
    return true;
}

bool CameraInterface::startCapture() {
    if (!is_open_) {
        std::cout << "Camera not open" << std::endl;
        return false;
    }
    
    // Stub implementation
    std::cout << "Starting camera capture" << std::endl;
    return true;
}

bool CameraInterface::stopCapture() {
    if (!is_open_) {
        return true;
    }
    
    // Stub implementation
    std::cout << "Stopping camera capture" << std::endl;
    is_open_ = false;
    return true;
}

bool CameraInterface::getFrame(Frame& frame) {
    if (!is_open_) {
        return false;
    }
    
    // Stub implementation - return dummy frame
    frame.width = width_;
    frame.height = height_;
    frame.channels = 3;
    frame.data.resize(width_ * height_ * frame.channels, 0);
    
    return true;
}

bool CameraInterface::isOpen() const {
    return is_open_;
}

int CameraInterface::getWidth() const {
    return width_;
}

int CameraInterface::getHeight() const {
    return height_;
}

int CameraInterface::getFPS() const {
    return fps_;
}

} // namespace vision
