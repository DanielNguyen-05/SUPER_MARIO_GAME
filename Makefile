BUILD_DIR := build
SRCS := $(wildcard source/def/*.cpp)
OBJS := $(SRCS:source/def/%.cpp=$(BUILD_DIR)/%.o)

TARGET := ./source/lib/run.exe

CXX := g++
CXXFLAGS := -std=c++11 -I./source/include

# Platform-specific flags
ifeq ($(shell uname), Darwin)  # macOS
    LDFLAGS := -L./source/lib/mac -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
else ifeq ($(OS), Windows_NT)  # Windows
    LDFLAGS := -L./source/lib/windows -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: source/def/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	cd ./source/lib && $(TARGET)

clean:
	rm -f $(BUILD_DIR)/* $(TARGET)

.PHONY: all clean run
