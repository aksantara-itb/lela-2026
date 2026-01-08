# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I./include -I./third_party/mavlink
LDFLAGS := -lpthread

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
BIN_DIR := bin

# Target executable
TARGET := $(BIN_DIR)/lela_mission

# Source files
COMMON_SRC := $(wildcard $(SRC_DIR)/common/*.cpp)
MAVLINK_SRC := $(wildcard $(SRC_DIR)/mavlink/*.cpp)
VISION_SRC := $(wildcard $(SRC_DIR)/vision/*.cpp)
MISSION_SRC := $(wildcard $(SRC_DIR)/mission/*.cpp)
MAIN_SRC := main.cpp

# All source files
SOURCES := $(COMMON_SRC) $(MAVLINK_SRC) $(VISION_SRC) $(MISSION_SRC) $(MAIN_SRC)

# Object files
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(filter $(SRC_DIR)/%,$(SOURCES)))
OBJECTS += $(BUILD_DIR)/main.o

# Module object files for separate compilation
COMMON_OBJ := $(patsubst $(SRC_DIR)/common/%.cpp,$(BUILD_DIR)/common/%.o,$(COMMON_SRC))
MAVLINK_OBJ := $(patsubst $(SRC_DIR)/mavlink/%.cpp,$(BUILD_DIR)/mavlink/%.o,$(MAVLINK_SRC))
VISION_OBJ := $(patsubst $(SRC_DIR)/vision/%.cpp,$(BUILD_DIR)/vision/%.o,$(VISION_SRC))
MISSION_OBJ := $(patsubst $(SRC_DIR)/mission/%.cpp,$(BUILD_DIR)/mission/%.o,$(MISSION_SRC))

# Default target
.PHONY: all
all: $(TARGET)

# Link target
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	@echo "Linking $@..."
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Build complete: $@"

# Build main.o
$(BUILD_DIR)/main.o: $(MAIN_SRC) | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build common module
$(BUILD_DIR)/common/%.o: $(SRC_DIR)/common/%.cpp | $(BUILD_DIR)/common
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build mavlink module
$(BUILD_DIR)/mavlink/%.o: $(SRC_DIR)/mavlink/%.cpp | $(BUILD_DIR)/mavlink
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build vision module
$(BUILD_DIR)/vision/%.o: $(SRC_DIR)/vision/%.cpp | $(BUILD_DIR)/vision
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build mission module
$(BUILD_DIR)/mission/%.o: $(SRC_DIR)/mission/%.cpp | $(BUILD_DIR)/mission
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/common:
	mkdir -p $(BUILD_DIR)/common

$(BUILD_DIR)/mavlink:
	mkdir -p $(BUILD_DIR)/mavlink

$(BUILD_DIR)/vision:
	mkdir -p $(BUILD_DIR)/vision

$(BUILD_DIR)/mission:
	mkdir -p $(BUILD_DIR)/mission

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean target
.PHONY: clean
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Clean complete"

# Run target
.PHONY: run
run: $(TARGET)
	@echo "Running $(TARGET)..."
	./$(TARGET)

# Help target
.PHONY: help
help:
	@echo "LELA 2026 - Mission Control System"
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  run     - Build and run the application"
	@echo "  help    - Show this help message"

# Module-specific targets for incremental builds
.PHONY: common mavlink vision mission
common: $(COMMON_OBJ)
	@echo "Common module built"

mavlink: $(MAVLINK_OBJ)
	@echo "MAVLink module built"

vision: $(VISION_OBJ)
	@echo "Vision module built"

mission: $(MISSION_OBJ)
	@echo "Mission module built"

# Dependency tracking
-include $(OBJECTS:.o=.d)

# Generate dependencies
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) -MM -MT $(@:.d=.o) $< > $@
