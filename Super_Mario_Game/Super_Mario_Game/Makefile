# Define the source files
SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)

# Define the target executable
TARGET := main

# Detect the operating system
UNAME_S := $(shell uname -s)

# Set compiler and linker flags based on the operating system
ifeq ($(UNAME_S), Darwin) # macOS
    CXX := clang++
    CXXFLAGS := -std=c++11 -I/opt/homebrew/include
    LDFLAGS := -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
else ifeq ($(OS), Windows_NT) # Windows
    CXX := g++
    CXXFLAGS := -std=c++11 -I../include
    LDFLAGS := -L../lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
else # Linux/Other Unix-like systems
    CXX := g++
    CXXFLAGS := -std=c++11 -I/usr/include
    LDFLAGS := -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif

# Default rule to build the target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
