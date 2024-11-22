BUILD_DIR := build

SRCS := $(wildcard source/*.cpp)
OBJS := $(SRCS:source/%.cpp=$(BUILD_DIR)/%.o)

TARGET := source/lib/run.exe

CXX := g++
CXXFLAGS := -std=c++11 -I./source/include
LDFLAGS := -L./source/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -mconsole

all: $(TARGET)
	@echo "Build complete. Running the program..."
	@./$(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $(TARGET))
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: source/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	@./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean run
