CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: 50

50: topological_sort.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f 50
