//
//  graph.cpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 25.04.25.
//

#include <queue>

#include "graph.hpp"

void bfs(const std::vector<std::vector<int>>& adj, int s) {
    std::vector<std::vector<int>>::size_type n = adj.size();
    std::vector<int> d(n, std::numeric_limits<int>::max());
    std::vector<Color> color(n, Color::white);
    std::vector<int> pi(n, -1);
    std::queue<int> q;
    
    d[s] = 0;
    color[s] = Color::gray;
    q.push(s);
    
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        
        for (int y : adj[x]) {
            if (color[y] == Color::white) {
                d[y] = d[x] + 1;
                color[y] = Color::gray;
                pi[y] = x;
                q.push(y);
            }
        }
        
        color[x] = Color::black;
    }
}

void bfs_visit(const std::vector<std::vector<int>>& adj, int s, std::vector<int>& d, std::vector<Color>& color, std::vector<int>& pi) {
    std::queue<int> q;
    
    d[s] = 0;
    color[s] = Color::gray;
    q.push(s);
    
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        
        for (int y : adj[x]) {
            if (color[y] == Color::white) {
                d[y] = d[x] + 1;
                color[y] = Color::gray;
                pi[y] = x;
                q.push(y);
            }
        }
        
        color[x] = Color::black;
    }
}

int count_components(const std::vector<std::vector<int>>& adj) {
    std::vector<std::vector<int>>::size_type n = adj.size();
    std::vector<int> d(n, std::numeric_limits<int>::max());
    std::vector<Color> color(n, Color::white);
    std::vector<int> pi(n, -1);
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (color[i] == Color::white) {
            bfs_visit(adj, i, d, color, pi);
            count++;
        }
    }
    
    return count;
}
