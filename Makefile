# Compiler and flags
CXX = g++
CXXFLAGS = -O2 -g -Wall -fmessage-length=0 -IC:/SFML-2.6.2/include -I./include
LDFLAGS = -LC:\SFML-2.6.2\lib -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = debug

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Target executable
TARGET = FinalProject.exe

# Rule to build the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Rule to build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create debug directory if it doesn't exist
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Convenience targets
all: $(TARGET)

# Clean target (Windows compatible)
clean:
	@if exist $(TARGET) del /f $(TARGET)
	@if exist $(BUILD_DIR) del /f $(BUILD_DIR)\*.o
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
