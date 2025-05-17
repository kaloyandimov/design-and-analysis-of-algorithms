//
//  graph.hpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 25.04.25.
//

#ifndef graph_hpp
#define graph_hpp

#include <vector>
#include <limits>

enum class Color {
    white,
    gray,
    black
};

void bfs(const std::vector<std::vector<int>>& adj, int s);

void dfs(const std::vector<std::vector<int>>& adj, int s);

int count_components(const std::vector<std::vector<int>>& adj);

#endif /* graph_hpp */
