# LELA 2026 - Mission Control System

A modular C++ project for autonomous mission control with MAVLink integration, vision processing, and mission management.

## Project Structure

```
lela-2026/
├── include/                 # Header files
│   ├── common/             # Common module (types, config, state)
│   ├── mavlink/            # MAVLink module (node, drop logic, servo, status)
│   ├── vision/             # Vision module (camera, hotspot detection)
│   └── mission/            # Mission module (mission controller)
├── src/                    # Source files
│   ├── common/
│   ├── mavlink/
│   ├── vision/
│   └── mission/
├── third_party/            # Third-party libraries
│   └── mavlink/           # MAVLink library (to be added)
├── main.cpp               # Application entry point
└── Makefile               # Build system
```

## Modules

### Common Module
- **types.h/cpp**: Common data types (Position, Velocity, Attitude, SystemStatus)
- **config.h/cpp**: Configuration management
- **state.h/cpp**: Thread-safe shared state management

### MAVLink Module
- **node.h/cpp**: MAVLink I/O node for vehicle communication
- **drop_logic.h/cpp**: Drop sequence logic and conditions
- **status_reporter.h/cpp**: Mission status reporting
- **servo_controller.h/cpp**: Servo control for drop mechanism

### Vision Module
- **camera_interface.h/cpp**: Camera capture interface
- **hotspot_detection.h/cpp**: Color-based hotspot detection

### Mission Module
- **mission_controller.h/cpp**: State machine for mission phases (IDLE, SEARCH, ALIGN, DROP, RETURN)

## Building

### Prerequisites
- g++ with C++17 support
- pthread library
- Make

### Build Commands

```bash
# Build the project
make

# Clean build artifacts
make clean

# Build and run
make run

# Show help
make help

# Build individual modules
make common
make mavlink
make vision
make mission
```

## Running

```bash
# Run with default configuration
./bin/lela_mission

# Run with custom configuration file
./bin/lela_mission config.txt
```

## Dependencies

The project expects MAVLink headers to be available in `third_party/mavlink/`.

## Notes

Current implementation includes stub functions for demonstration purposes. Full implementation requires:
- MAVLink library integration
- Camera driver integration (e.g., V4L2, OpenCV)
- Image processing for hotspot detection
- Navigation and control algorithms
