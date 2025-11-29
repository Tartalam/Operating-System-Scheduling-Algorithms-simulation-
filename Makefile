# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -O2
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O3

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Target executable
TARGET = $(BIN_DIR)/scheduling_simulator

# Default target
all: release

# Release build
release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

# Create directories
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files to create executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Clean and rebuild
rebuild: clean all

# Run the program
run: release
	./$(TARGET)

# Debug run
debug-run: debug
	./$(TARGET)

# Install (copy executable to system path, optional)
install: release
	@echo "Installing to /usr/local/bin (may require sudo)"
	sudo cp $(TARGET) /usr/local/bin/scheduling_simulator

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/scheduling_simulator

# Show help
help:
	@echo "Available targets:"
	@echo "  all/release - Build release version (default)"
	@echo "  debug       - Build debug version with symbols"
	@echo "  clean       - Remove all build artifacts"
	@echo "  rebuild     - Clean and rebuild"
	@echo "  run         - Build release version and run"
	@echo "  debug-run   - Build debug version and run"
	@echo "  install     - Install to system path (requires sudo)"
	@echo "  uninstall   - Uninstall from system path"
	@echo "  help        - Show this help message"

# Phony targets
.PHONY: all release debug clean rebuild run debug-run install uninstall help

# Dependency tracking (optional but recommended)
-include $(OBJS:.o=.d)

# Generate dependency files
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) -MM -MT $(BUILD_DIR)/%.o $< > $@