# Define the build directory
BUILD_DIR := build

# Define source files and object files
SRCS := $(wildcard source/def/*.cpp)
OBJS := $(SRCS:source/def/%.cpp=$(BUILD_DIR)/%.o)

# Define the target executable (add .exe for Windows)
TARGET := source/lib/run

# Define the compiler and flags
CXX := g++
CXXFLAGS := -std=c++11

# Include SFML headers (use the appropriate folder based on OS)
ifeq ($(shell uname), Darwin)  # macOS
    SFML_INCLUDE := ./source/include/mac/
    SFML_LIB := ./source/lib/mac
    LDFLAGS := -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -rpath $(SFML_LIB)
    CXXFLAGS += -I$(SFML_INCLUDE)
else ifeq ($(OS), Windows_NT)  # Windows
    SFML_INCLUDE := ./source/include/windows/
    SFML_LIB := ./source/lib/windows
    LDFLAGS := -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    CXXFLAGS += -I$(SFML_INCLUDE)
    TARGET := source/lib/run.exe  # Ensure the target has a .exe extension
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
	@./$(TARGET)

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean run
