# Compiler and target executable
CXX = g++
TARGET = main

# Source and object files
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Compiler and linker flags
CXXFLAGS = -std=c++11 -I../include
LDFLAGS = -L../lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Build the target executable
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)
