BUILD_DIR := build
SRCS := $(wildcard source/def/*.cpp)
OBJS := $(SRCS:source/def/%.cpp=$(BUILD_DIR)/%.o)

TARGET := ./source/run.exe

CXX := g++
CXXFLAGS := -std=c++11 -I./source/include
LDFLAGS := -L./source/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -mwindows

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