#pragma once

#include <unordered_set>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace gutils
{

typedef unsigned int vertex_t;
typedef std::pair<vertex_t, vertex_t> Edge;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

Graph generate_graph(vertex_t vertexCount, unsigned int edgeCount);
Graph generate_tree(vertex_t vertexCount);

vertex_t get_full_graph_edge_count(vertex_t vertex);
std::vector<vertex_t> generate_prufer_code(vertex_t vertexCount);

} // namespace gutils
