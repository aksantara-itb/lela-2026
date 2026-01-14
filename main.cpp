// #include <iostream>
// #include <chrono>
// #include <thread>

// // Common module
// #include "common/types.h"
// #include "common/config.h"
// #include "common/state.h"

// // MAVLink module
// #include "mavlink/node.h"
// #include "mavlink/drop_logic.h"
// #include "mavlink/status_reporter.h"
// #include "mavlink/servo_controller.h"

// // Vision module
// #include "vision/camera_interface.h"
// #include "vision/hotspot_detection.h"

// // Mission module
// #include "mission/mission_controller.h"

// int main(int argc, char* argv[]) {
//     std::cout << "=== LELA 2026 - Mission Control System ===" << std::endl;
    
//     // Initialize configuration
//     common::Config config;
//     if (argc > 1) {
//         config.load(argv[1]);
//     }
    
//     // Initialize shared state
//     common::SharedState& state = common::SharedState::getInstance();
//     state.setSystemStatus(common::SystemStatus::IDLE);
    
//     // Initialize MAVLink components
//     mavlink::MavlinkNode mavlink_node;
//     mavlink::DropLogic drop_logic;
//     mavlink::StatusReporter status_reporter;
//     mavlink::ServoController servo_controller;
    
//     if (!mavlink_node.initialize("udp://0.0.0.0", config.getMavlinkPort())) {
//         std::cerr << "Failed to initialize MAVLink node" << std::endl;
//         return 1;
//     }
    
//     drop_logic.initialize();
//     drop_logic.setDropAltitude(config.getDropAltitude());
    
//     status_reporter.initialize();
    
//     if (!servo_controller.initialize()) {
//         std::cerr << "Failed to initialize servo controller" << std::endl;
//         return 1;
//     }
    
//     // Initialize vision components
//     vision::CameraInterface camera;
//     vision::HotspotDetection hotspot_detector;
    
//     if (!camera.initialize(config.getCameraDevice())) {
//         std::cerr << "Failed to initialize camera" << std::endl;
//         return 1;
//     }
    
//     hotspot_detector.initialize();
    
//     // Initialize mission controller
//     mission::MissionController mission_controller;
//     if (!mission_controller.initialize()) {
//         std::cerr << "Failed to initialize mission controller" << std::endl;
//         return 1;
//     }
    
//     // Start MAVLink node
//     mavlink_node.start();
    
//     // Start camera capture
//     if (!camera.startCapture()) {
//         std::cerr << "Failed to start camera capture" << std::endl;
//         return 1;
//     }
    
//     std::cout << "System initialized successfully" << std::endl;
//     std::cout << "Starting mission..." << std::endl;
    
//     // Start mission
//     mission_controller.startMission();
    
//     // Main loop
//     int loop_count = 0;
//     const int MAX_LOOPS = 20;  // Run for limited iterations in stub
    
//     while (loop_count < MAX_LOOPS) {
//         // Get camera frame
//         vision::Frame frame;
//         if (camera.getFrame(frame)) {
//             // Detect hotspots
//             std::vector<vision::Hotspot> hotspots;
//             if (hotspot_detector.detectHotspots(frame, hotspots)) {
//                 vision::Hotspot best_hotspot;
//                 if (hotspot_detector.getBestHotspot(hotspots, best_hotspot)) {
//                     // Update shared state
//                     state.setTargetDetected(true);
                    
//                     // Check if centered and ready to drop
//                     if (hotspot_detector.isHotspotCentered(best_hotspot, frame)) {
//                         if (drop_logic.canDrop()) {
//                             std::cout << "Executing drop..." << std::endl;
//                             drop_logic.executeDrop();
//                             servo_controller.triggerDrop();
//                         }
//                     }
//                 }
//             }
//         }
        
//         // Update mission controller
//         mission_controller.update();
        
//         // Report status periodically
//         if (loop_count % 5 == 0) {
//             status_reporter.reportStatus(state.getSystemStatus());
//             status_reporter.reportMissionProgress(mission_controller.getProgressPercent());
//         }
        
//         // Check if mission is completed
//         if (mission_controller.getState() == mission::MissionState::COMPLETED) {
//             std::cout << "Mission completed successfully!" << std::endl;
//             break;
//         }
        
//         // Sleep for loop cycle
//         std::this_thread::sleep_for(std::chrono::milliseconds(100));
//         loop_count++;
//     }
    
//     // Cleanup
//     std::cout << "Shutting down..." << std::endl;
//     mission_controller.stopMission();
//     camera.stopCapture();
//     mavlink_node.stop();
    
//     std::cout << "System shutdown complete" << std::endl;
//     return 0;
// }

#include "mavlink/node.h"
#include "mavlink/servo_controller.h"
#include "mavlink/status_reporter.h"

#include <unistd.h>   // for sleep()

int main() {
    mavlink::MavlinkNode node;

    // 🔴 REQUIRED: announce yourself first
    node.sendHeartbeat();
    sleep(1);   // give MAVProxy/QGC time to register the system

    // mavlink::ServoController servo(node);
    mavlink::StatusReporter status(node);

    // Open servo
    // servo.open();
    // sleep(1);

    // Close servo
    // servo.close();
    // sleep(1);

    // Send one status message
    status.send("Servo open/close test completed", 6);

    return 0;
}
