# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Icontainer

# Executable name
TARGET = demo

# Source files
SRCS = Demo.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run with Valgrind (detailed)
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean valgrind
