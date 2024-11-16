# Define the build directory
BUILD_DIR := build

# Define source files and object files
SRCS := $(wildcard source/def/*.cpp)
OBJS := $(SRCS:source/def/%.cpp=$(BUILD_DIR)/%.o)

# Define the target executable (không cần .exe trên macOS)
TARGET := source/lib/run

# Define the compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -I./source/include -I/opt/homebrew/include

# Define the linker flags
ifeq ($(shell uname), Darwin)  # macOS
    LDFLAGS := -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
else ifeq ($(OS), Windows_NT)  # Windows
    LDFLAGS := -L./source/lib/windows -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	@mkdir -p $(dir $(TARGET))
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Rule to build object files
$(BUILD_DIR)/%.o: source/def/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean run
