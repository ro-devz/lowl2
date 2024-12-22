# Compiler and flags
CXX = g++
CXXFLAGS = -O2 -g -Wall -fmessage-length=0 -IC:/SFML-2.6.2/include -I./include
LDFLAGS = -LC:/SFML-2.6.2/lib
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
OBJ_DIR = obj

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Target executable
TARGET = $(BIN_DIR)/FinalProject.exe

# Ensure directories exist
$(shell if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)")
$(shell if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)")

# Main target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	@echo Linking...
	@$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LDLIBS)
	@echo Build complete!

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo Compiling $<...
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target for Windows
clean:
	@echo Cleaning...
	@if exist "bin\\FinalProject.exe" del /q "bin\\FinalProject.exe"
	@if exist "$(OBJ_DIR)" rd /s /q "$(OBJ_DIR)"
	@echo Clean complete!

# Rebuild everything
rebuild: clean all

# Help target
help:
	@echo Available targets:
	@echo   all      - Build the project (default)
	@echo   clean    - Remove all built files
	@echo   rebuild  - Clean and rebuild the project
	@echo   help     - Show this help message

.PHONY: all clean rebuild help