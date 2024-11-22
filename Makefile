# Directories
BUILD_DIR := build
SRC_DIR := source
INCLUDE_DIR := $(SRC_DIR)/include
LIB_DIR := $(SRC_DIR)/lib

# Source files and objects
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Target executable
TARGET := $(LIB_DIR)/run.exe

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -I$(INCLUDE_DIR)
LDFLAGS := -L$(LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -mconsole

# Default rule
all: $(TARGET)
	@echo "Build complete!"
	@echo "Running the program..."
	@./$(TARGET)

# Link target
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile source files
$(OBJS): | compile-message

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

compile-message:
	@echo "Compiling..."

# Run target
run: $(TARGET)
	@./$(TARGET)

# Clean build files
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR) $(TARGET)

# Phony targets
.PHONY: all clean run
