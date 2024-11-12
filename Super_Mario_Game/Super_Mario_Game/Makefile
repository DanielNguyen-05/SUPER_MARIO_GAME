# Define the compiler
CXX = g++

# Define the target executable
TARGET = main

# Define the source files
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Detect the operating system
UNAME_S := $(shell uname -s)

# Set compiler and linker flags based on the operating system
ifeq ($(UNAME_S), Darwin)  # Darwin là tên hệ điều hành của macOS
    CXXFLAGS = -std=c++11 -I/opt/homebrew/Cellar/sfml/2.6.1/include
    LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
else ifeq ($(OS), Windows_NT)  # Windows_NT là tên hệ điều hành của Windows trong Makefile
    CXXFLAGS = -std=c++11 -I../include
    LDFLAGS = -L../lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif

# Default rule to build the target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to build the object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)
