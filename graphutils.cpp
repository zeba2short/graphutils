#include <vector>
#include <utility>
#include <algorithm>

#include "graphutils.h"

namespace gutils
{

std::vector<unsigned int> generate_prufer_code(unsigned int vertexCount)
{
	srand(time(NULL));

	unsigned int edgeCount = vertexCount - 2;
	std::vector<unsigned int> vertex(edgeCount);
	for (unsigned int i = 1; i < edgeCount; ++i)
		vertex[i] = rand() % (vertexCount - 1) + 1;
	return vertex;
}

std::vector<Edge> generate_tree_edge(const std::vector<vertex_t>& pruferCode)
{
	vertex_t vertexCount = pruferCode.size() + 2;
	std::vector<vertex_t> neighborCount(vertexCount, 1);

	for (const auto v: pruferCode)
		++neighborCount[v];

	vertex_t leafNum = std::find(neighborCount.begin(), neighborCount.end(), 1) - neighborCount.begin();
	vertex_t newFreeLeafNum = vertexCount;

	std::vector<Edge> edges;

	for (const auto v: pruferCode)
	{
		if (leafNum < newFreeLeafNum)
		{
			edges.push_back(std::make_pair(leafNum, v));
			--neighborCount[leafNum];
			leafNum = std::find(neighborCount.begin() + leafNum, neighborCount.end(), 1) - neighborCount.begin();
		}
		else
		{
			edges.push_back(std::make_pair(newFreeLeafNum, v));
			--neighborCount[newFreeLeafNum];
		}

		--neighborCount[v];
		newFreeLeafNum = (neighborCount[v] == 1) ? v : vertexCount;
	}

	vertex_t begin = std::find(neighborCount.begin(), neighborCount.end(), 1) - neighborCount.begin();
	vertex_t end = std::find(neighborCount.begin() + begin + 1, neighborCount.end(), 1) - neighborCount.begin();

	edges.push_back(std::make_pair(begin, end));

	return edges;
}

unsigned int get_full_graph_edge_count(vertex_t vertex)
{
	return vertex * (vertex - 1) / 2;
}

std::set<Edge>
generate_uniq_edges(vertex_t vertexCount, unsigned int edgeCount)
{
	srand(time(NULL));
	std::set<Edge> edges;

	while(edges.size() != edgeCount)
	{
		vertex_t begin = rand() % vertexCount;
		vertex_t end = rand() % vertexCount;

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

Graph generate_graph(vertex_t vertexCount, unsigned int edgeCount)
{
	Graph graph(vertexCount);
	for (const auto& edge: generate_uniq_edges(vertexCount, edgeCount))
	{
		add_edge(edge.first, edge.second, graph);
	}
	return graph;
}

Graph generate_tree(vertex_t vertexCount)
{
	Graph graph(vertexCount);
	auto pruferCode = generate_prufer_code(vertexCount);
	for (const auto& edge: generate_tree_edge(pruferCode))
		add_edge(edge.first, edge.second, graph);
	return graph;
}

} // namespace gutils
