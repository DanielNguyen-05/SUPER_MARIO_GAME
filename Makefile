BUILD_DIR := build

SRCS := $(wildcard source/def/*.cpp)
OBJS := $(SRCS:source/def/%.cpp=$(BUILD_DIR)/%.o)

TARGET := source/lib/run

CXX := g++
CXXFLAGS := -std=c++11

ifeq ($(shell uname), Darwin)
    ifeq ($(shell brew list sfml),) 
        SFML_INCLUDE := ./source/include
        SFML_LIB := ./source/lib
        LDFLAGS := -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -rpath $(SFML_LIB)
        CXXFLAGS += -I$(SFML_INCLUDE)
    else
        SFML_INCLUDE := /opt/homebrew/include
        SFML_LIB := /opt/homebrew/lib
        LDFLAGS := -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
        CXXFLAGS += -I$(SFML_INCLUDE)
    endif
else ifeq ($(OS), Windows_NT)
    SFML_INCLUDE := ./source/include
    SFML_LIB := ./source/lib
    LDFLAGS := -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    CXXFLAGS += -I$(SFML_INCLUDE)
    TARGET := source/lib/run.exe
endif

all: $(TARGET)
	@./$(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $(TARGET))
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: source/def/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	@./$(TARGET) 

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
