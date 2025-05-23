//
//  graph.hpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 25.04.25.
//

#ifndef graph_hpp
#define graph_hpp

#include <optional>
#include <utility>
#include <vector>

enum class Color {
    white,
    gray,
    black
};

using AdjacencyList = std::vector<std::vector<int>>;

void breadth_first_search(const AdjacencyList& adj);

void depth_first_search(const AdjacencyList& adj);

int count_components(const AdjacencyList& adj);

AdjacencyList transpose(const AdjacencyList& adj);

std::vector<int> tarjan_topological_sort(const AdjacencyList& adj);

std::optional<std::vector<int>> kahn_topological_sort(const AdjacencyList& adj);

std::vector<std::vector<int>> kosaraju_find_scc(const AdjacencyList& adj);

std::vector<int> find_cut_vertices(const AdjacencyList& adj);

std::vector<std::pair<int, int>> find_cut_edges(const AdjacencyList& adj);

#endif /* graph_hpp */
