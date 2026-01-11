#ifndef COMMON_CONFIG_H
#define COMMON_CONFIG_H

#include <cstdint>

/* ============================================================
 * MAVLINK IDENTITY CONFIGURATION
 * ============================================================ */

// Companion computer identity (Raspberry Pi)
constexpr uint8_t MAVLINK_SYSTEM_ID    = 42;   // Choose unique ID
constexpr uint8_t MAVLINK_COMPONENT_ID = 190;  // MAV_COMP_ID_ONBOARD_COMPUTER

// Target Flight Controller identity
constexpr uint8_t FC_SYSTEM_ID         = 1;
constexpr uint8_t FC_COMPONENT_ID      = 1;


/* ============================================================
 * MAVLINK CONNECTION CONFIGURATION
 * ============================================================ */

// Default MAVLink UDP connection
constexpr int MAVLINK_UDP_PORT = 14550;

// MAVLink channel (usually 0 is fine)
constexpr uint8_t MAVLINK_CHANNEL = 0;


/* ============================================================
 * SERVO (DROP MECHANISM) CONFIGURATION
 * ============================================================ */

// Servo channel used for dropping payload
constexpr uint8_t DROP_SERVO_CHANNEL = 9;

// PWM values (microseconds)
constexpr uint16_t DROP_SERVO_OPEN_PWM  = 1900;
constexpr uint16_t DROP_SERVO_CLOSE_PWM = 1100;

// Safety delay (ms) before closing servo after drop
constexpr int DROP_SERVO_CLOSE_DELAY_MS = 800;


/* ============================================================
 * DROP LOGIC CONSTRAINTS
 * ============================================================ */

// Altitude constraints (meters)
constexpr float DROP_ALTITUDE_MIN = 20.0f;
constexpr float DROP_ALTITUDE_MAX = 50.0f;

// Optional: waypoint index at which drop is allowed
constexpr int DROP_WAYPOINT_INDEX = 3;


/* ============================================================
 * CAMERA CONFIGURATION
 * ============================================================ */

// OpenCV camera index
constexpr int CAMERA_INDEX = 0;

// Camera resolution (optional)
constexpr int CAMERA_WIDTH  = 640;
constexpr int CAMERA_HEIGHT = 480;


/* ============================================================
 * HSV COLOR DETECTION THRESHOLDS
 * ============================================================ */

// RED color
constexpr int RED_H_MIN = 0;
constexpr int RED_H_MAX = 10;
constexpr int RED_S_MIN = 120;
constexpr int RED_S_MAX = 255;
constexpr int RED_V_MIN = 70;
constexpr int RED_V_MAX = 255;

// BLUE color
constexpr int BLUE_H_MIN = 100;
constexpr int BLUE_H_MAX = 130;
constexpr int BLUE_S_MIN = 150;
constexpr int BLUE_S_MAX = 255;
constexpr int BLUE_V_MIN = 50;
constexpr int BLUE_V_MAX = 255;


/* ============================================================
 * STATUS TEXT SETTINGS
 * ============================================================ */

// Maximum length allowed by MAVLink STATUSTEXT
constexpr int MAVLINK_STATUSTEXT_MAX_LEN = 50;

// Default severity
constexpr uint8_t MAVLINK_STATUSTEXT_SEVERITY_INFO = 6; // MAV_SEVERITY_INFO
constexpr uint8_t MAVLINK_STATUSTEXT_SEVERITY_WARN = 4; // MAV_SEVERITY_WARNING
constexpr uint8_t MAVLINK_STATUSTEXT_SEVERITY_ERR  = 3; // MAV_SEVERITY_ERROR


/* ============================================================
 * THREAD TIMING
 * ============================================================ */

// MAVLink receive loop delay (ms)
constexpr int MAVLINK_RX_LOOP_DELAY_MS = 5;

// Vision processing loop delay (ms)
constexpr int VISION_LOOP_DELAY_MS = 20;

#endif // COMMON_CONFIG_H
