CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Icontainer
TARGET = demo
TEST_DIR = tests
TESTS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_BINS = $(TESTS:.cpp=)

all: $(TARGET)

$(TARGET): Demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(TEST_DIR)/%: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

test: $(TEST_BINS)
	@for t in $(TEST_BINS); do \
		valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$$t || exit 1; \
	done

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(TARGET) $(TEST_BINS)

.PHONY: all test clean valgrind
