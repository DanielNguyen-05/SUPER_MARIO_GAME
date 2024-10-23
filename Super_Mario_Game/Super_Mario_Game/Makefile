# Define the compiler
CXX = g++

# Define the compiler flags
CXXFLAGS = -std=c++11 -I/opt/homebrew/Cellar/sfml/2.6.1/include

# Define the linker flags
LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

# Define the target executable
TARGET = main

# Define the source files
SRCS = $(wildcard src/*.cpp)  # Automatically find all .cpp files in src

# Define the object files
OBJS = $(SRCS:.cpp=.o)

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
