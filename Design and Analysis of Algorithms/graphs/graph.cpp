//
//  graph.cpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 25.04.25.
//

#include <queue>

#include "graph.hpp"

void breadth_first_search_visit(const AdjacencyList& adj, std::vector<int>& d, std::vector<Color>& color, std::vector<int>& pi, int s) {
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

void breadth_first_search(const AdjacencyList& adj) {
    int n = static_cast<int>(adj.size());
    std::vector<int> d(n);
    std::vector<Color> color(n, Color::white);
    std::vector<int> pi(n, -1);
    
    for (int i = 0; i < n; i++) {
        if (color[i] == Color::white) {
            breadth_first_search_visit(adj, d, color, pi, i);
        }
    }
}

void depth_first_search_visit(const AdjacencyList& adj, std::vector<int>& d, std::vector<int>& f, std::vector<Color>& color, std::vector<int>& pi, int& time, int x) {
    d[x] = ++time;
    color[x] = Color::gray;
    
    for (int y : adj[x]) {
        if (color[y] == Color::white) {
            pi[y] = x;
            
            depth_first_search_visit(adj, d, f, color, pi, time, y);
        }
    }
    
    color[x] = Color::black;
    f[x] = ++time;
}

void depth_first_search(const AdjacencyList& adj) {
    int n = static_cast<int>(adj.size());
    std::vector<int> d(n);
    std::vector<int> f(n);
    std::vector<Color> color(n, Color::white);
    std::vector<int> pi(n, -1);
    int time = 0;
    
    for (int i = 0; i < n; i++) {
        if (color[i] == Color::white) {
            depth_first_search_visit(adj, d, f, color, pi, time, i);
        }
    }
}

int count_components(const AdjacencyList& adj) {
    int n = static_cast<int>(adj.size());
    std::vector<int> d(n);
    std::vector<Color> color(n, Color::white);
    std::vector<int> pi(n, -1);
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (color[i] == Color::white) {
            count++;
            
            breadth_first_search_visit(adj, d, color, pi, i);
        }
    }
    
    return count;
}

AdjacencyList transpose(const AdjacencyList& adj) {
    int n = static_cast<int>(adj.size());
    AdjacencyList transposed(n);
    
    for (int x = 0; x < n; x++) {
        for (int y : adj[x]) {
            transposed[y].push_back(x);
        }
    }
    
    return transposed;
}

void tarjan_topological_sort_rec(const AdjacencyList& adj, std::vector<Color>& colors, std::vector<int>& order, int x) {
    colors[x] = Color::gray;
    
    for (int y : adj[x]) {
        if (colors[y] == Color::white) {
            tarjan_topological_sort_rec(adj, colors, order, y);
        }
    }
    
    colors[x] = Color::black;
    order.push_back(x);
}

std::vector<int> tarjan_topological_sort(const AdjacencyList& adj) {
    int n = static_cast<int>(adj.size());
    std::vector<Color> colors(n, Color::white);
    std::vector<int> order;
    
    for (int i = 0; i < n; i++) {
        if (colors[i] == Color::white) {
            tarjan_topological_sort_rec(adj, colors, order, i);
        }
    }
    
    return std::vector(order.crbegin(), order.crend());
}

void kosaraju_find_scc_rec(const AdjacencyList& adj, std::vector<Color>& colors, std::vector<int>& component, int x) {
    colors[x] = Color::gray;
    component.push_back(x);
    
    for (int y : adj[x]) {
        if (colors[y] == Color::white) {
            kosaraju_find_scc_rec(adj, colors, component, y);
        }
    }
    
    colors[x] = Color::black;
}

std::vector<std::vector<int>> kosaraju_find_scc(const AdjacencyList& adj) {
    AdjacencyList transposed = transpose(adj);
    std::vector<int> order = tarjan_topological_sort(adj);
    std::vector<Color> colors(adj.size(), Color::white);
    std::vector<std::vector<int>> components;
    std::vector<int> component;
    
    for (int x : order) {
        if (colors[x] == Color::white) {
            component.clear();
            kosaraju_find_scc_rec(transposed, colors, component, x);
            components.push_back(component);
        }
    }
    
    return components;
}
