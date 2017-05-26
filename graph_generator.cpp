#include <set>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;

typedef std::pair<unsigned int, unsigned int> Edge;
typedef adjacency_list<vecS, vecS, undirectedS> Graph;

void usage(const std::string& name)
{
	std::cout << "Usage: " << name << " <vertex count> <edge count>\n";
}

unsigned int get_full_graph_edge_count(unsigned int vertex)
{
	return vertex * (vertex - 1) / 2;
}

std::set<Edge>
generate_uniq_edges(unsigned int vertexCount, unsigned int edgeCount)
{
	srand(time(NULL));
	std::set<Edge> edges;

	while(edges.size() != edgeCount)
	{
		unsigned int begin = rand() % vertexCount;
		unsigned int end = rand() % vertexCount;

		if (begin > end)
		{
			std::swap(begin, end);
		}

		if (begin != end)
		{
			edges.insert({begin, end});
		}
	}

	return edges;
}

Graph generate_graph(unsigned int vertexCount, unsigned int edgeCount)
{
	Graph graph(vertexCount);
	for (const auto& edge: generate_uniq_edges(vertexCount, edgeCount))
	{
		add_edge(edge.first, edge.second, graph);
	}
	return graph;
}

int main(int argc, const char *argv[])
{
	if (argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	const unsigned int vertexCount = std::stoi(argv[1]);
	const unsigned int edgeCount = std::stoi(argv[2]);

	if (get_full_graph_edge_count(vertexCount) < edgeCount)
	{
		std::cerr << "edge count more then in full graph\n";
		return 1;
	}

	auto graph = generate_graph(vertexCount, edgeCount);
	write_graphviz(std::cout, graph);

	return 0;
}
