CXX=g++
CXXFLAGS=--std=c++11 -Wall -Werror

graph_generator:
	$(CXX) $(CXXFLAGS) graph_generator.cpp -o $@
