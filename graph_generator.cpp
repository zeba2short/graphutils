#include <set>
#include <ctime>
#include <string>
#include <cstdlib>
#include <iostream>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>

#include "graphutils.h"

void usage(const std::string& name)
{
	std::cout << "Usage:\n";
	std::cout<< "\t" << name << " -r <vertex count> <edge count> --- generate random graph\n";
	std::cout<< "\t" << name << " -t <vertex count>              --- generate random tree\n";
}

int main(int argc, const char *argv[])
{
	if (argc < 3)
	{
		usage(argv[0]);
		return 1;
	}

	if (std::string(argv[1]) == "-r")
	{
		const unsigned int vertexCount = std::stoi(argv[2]);
		const unsigned int edgeCount = std::stoi(argv[3]);

		if (gutils::get_full_graph_edge_count(vertexCount) < edgeCount)
		{
			std::cerr << "edge count more then in full graph\n";
			return 1;
		}

		auto graph = gutils::generate_graph(vertexCount, edgeCount);
		write_graphviz(std::cout, graph);
	}
	else if (std::string(argv[1]) == "-t")
	{
		const unsigned int vertexCount = std::stoi(argv[2]);
		auto graph = gutils::generate_tree(vertexCount);
		write_graphviz(std::cout, graph);
	}

	return 0;
}
