//
//  graph.cpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 25.04.25.
//

#include <queue>

#include "helper.hpp"
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

std::vector<int> calculate_in_degrees(const AdjacencyList& adj) {
    std::vector<int> in_degree(adj.size());
    
    for (const std::vector<int>& ys : adj) {
        for (int y : ys) {
            in_degree[y]++;
        }
    }
    
    return in_degree;
}

std::optional<std::vector<int>> kahn_topological_sort(const AdjacencyList& adj) {
    int n = static_cast<int>(adj.size());
    std::vector<int> in_degree = calculate_in_degrees(adj);
    std::vector<Color> color(n, Color::white);
    std::vector<int> order;
    std::queue<int> q;
    
    order.reserve(n);
    
    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            color[i] = Color::gray;
            q.push(i);
        }
    }
    
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        
        order.push_back(x);
        
        for (int y : adj[x]) {
            in_degree[y]--;
            
            if (in_degree[y] == 0) {
                color[y] = Color::gray;
                q.push(y);
            }
        }
        
        color[x] = Color::black;
    }
    
    if (order.size() < n) {
        return std::nullopt;
    }
    
    return std::optional<std::vector<int>>{order};
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

int find_cut_vertices_rec(const AdjacencyList& adj, std::vector<int>& level, std::vector<Color>& color, std::vector<int>& cut_vertices, int x, int l) {
    bool is_cut_vertex = false;
    bool is_root = false;
    int minback = l;
    int count = 0;
    
    if (l == 0) {
        is_root = true;
    }
    
    color[x] = Color::gray;
    level[x] = l;
    
    for (int y : adj[x]) {
        if (color[y] == Color::white) {
            int b = find_cut_vertices_rec(adj, level, color, cut_vertices, y, l + 1);
            
            if (b >= level[x] && !is_root) {
                is_cut_vertex = true;
            }
            
            minback = std::min(minback, b);
            count++;
        } else if (color[y] == Color::gray) {
            if (level[y] < minback && level[y] != level[x] - 1) {
                minback = level[y];
            }
        }
    }
    
    if (is_cut_vertex || (is_root && count >= 2)) {
        cut_vertices.push_back(x);
    }
    
    color[x] = Color::black;
    
    return minback;
}

std::vector<int> find_cut_vertices(const AdjacencyList& adj) {
    int n = static_cast<int>(adj.size());
    std::vector<Color> color(n, Color::white);
    std::vector<int> level(n);
    std::vector<int> cut_vertices;
    
    int x = get_random_number(n - 1);
    
    find_cut_vertices_rec(adj, level, color, cut_vertices, x, 0);
    
    return cut_vertices;
}

int find_cut_edges_rec(const AdjacencyList& adj, std::vector<int>& level, std::vector<Color>& colors, std::vector<std::pair<int, int>>& cut_edges, int x, int l) {
    int minback = l;
    
    colors[x] = Color::gray;
    level[x] = l;
    
    for (int y : adj[x]) {
        if (colors[y] == Color::white) {
            int b = find_cut_edges_rec(adj, level, colors, cut_edges, y, l + 1);
            
            if (b > level[x]) {
                cut_edges.emplace_back(x, y);
            } else {
                minback = std::min(minback, b);
            }
        }
        else if (colors[y] == Color::gray) {
            if (level[y] < minback && level[y] != level[x] - 1) {
                minback = level[y];
            }
        }
    }
    
    colors[x] = Color::black;
    
    return minback;
}

std::vector<std::pair<int, int>> find_cut_edges(const AdjacencyList& adj) {
    int n = static_cast<int>(adj.size());
    std::vector<Color> color(n, Color::white);
    std::vector<int> level(n);
    std::vector<std::pair<int, int>> cut_edges;
    
    int x = get_random_number(n - 1);
    
    find_cut_edges_rec(adj, level, color, cut_edges, x, 0);
    
    return cut_edges;
}
