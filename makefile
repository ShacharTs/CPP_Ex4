CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -g -Icontainer

TARGET := main

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<


TEST_BIN := tests/test

$(TEST_BIN): tests/test.cpp tests/People.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^


test: $(TEST_BIN)
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TEST_BIN)


clean:
	rm -f $(TARGET) $(TEST_BIN)

.PHONY: all test clean
