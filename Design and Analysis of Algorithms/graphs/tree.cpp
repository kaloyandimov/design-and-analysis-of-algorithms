//
//  tree.cpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 17.05.25.
//

#include <algorithm>
#include <ranges>

#include "helper.hpp"
#include "tree.hpp"

TreeNode::TreeNode(int x) : data(x) {}

std::unique_ptr<TreeNode> build_rooted_tree_rec(const AdjacencyList& adj, int x, int parent) {
    auto root = std::make_unique<TreeNode>(x);
    
    for (int y : adj[x]) {
        if (y != parent) {
            root->children.push_back(build_rooted_tree_rec(adj, y, x));
        }
    }
    
    return root;
}

std::unique_ptr<TreeNode> build_rooted_tree(const AdjacencyList& adj, int s) {
    return build_rooted_tree_rec(adj, s, -1);
}

template <typename... Vecs>
int sum_nodes_max_value(const std::vector<std::unique_ptr<TreeNode>>& nodes, const Vecs&... vecs) {
    auto values = nodes | std::views::transform([&](const std::unique_ptr<TreeNode>& node) {
        return std::max({vecs[node->data]...});
    });

    return std::accumulate(values.begin(), values.end(), 0);
}

void independence_number_rec(TreeNode* node, std::vector<int>& a, std::vector<int>& b) {
    if (node->children.empty()) {
        a[node->data] = 1;
        b[node->data] = 0;
        return;
    }
    
    for (const auto& child : node->children) {
        independence_number_rec(child.get(), a, b);
    }
    
    a[node->data] = 1 + sum_nodes_max_value(node->children, b);
    b[node->data] = sum_nodes_max_value(node->children, a, b);
}

int independence_number(const AdjacencyList& adj) {
    if (adj.empty()) {
        return 0;
    }
    
    int n = static_cast<int>(adj.size());
    std::vector<int> a(n);
    std::vector<int> b(n);
    int root = get_random_number(n - 1);
    auto tree = build_rooted_tree(adj, root);
    
    independence_number_rec(tree.get(), a, b);
    
    return std::max(a[root], b[root]);
}

int vertex_cover_size(const AdjacencyList& adj) {
    return static_cast<int>(adj.size()) - independence_number(adj);
}

int sum_min_child(const std::vector<std::unique_ptr<TreeNode>>& children, const std::vector<int>& a, const std::vector<int>& b, int sum_a) {
    auto values = children | std::views::transform([&](const std::unique_ptr<TreeNode>& child) {
        return sum_nodes_max_value(child->children, b) + sum_a - a[child->data];
    });
    
    return std::ranges::min(values);
}

void dominating_number_rec(TreeNode* node, std::vector<int>& a, std::vector<int>& b) {
    if (node->children.empty()) {
        a[node->data] = 1;
        b[node->data] = 0;
        return;
    }
    
    for (const auto& child : node->children) {
        dominating_number_rec(child.get(), a, b);
    }
    
    int sum_a = sum_nodes_max_value(node->children, a);
    int sum_b = sum_nodes_max_value(node->children, b);
    int sum_c = sum_min_child(node->children, a, b, sum_a);
    
    a[node->data] = 1 + std::min(sum_b, sum_c);
    b[node->data] = std::min(1 + sum_b, sum_a);
}

int dominating_number(const AdjacencyList& adj) {
    if (adj.empty()) {
        return 0;
    }
    
    int n = static_cast<int>(adj.size());
    std::vector<int> a(n);
    std::vector<int> b(n);
    int root = get_random_number(n - 1);
    auto tree = build_rooted_tree(adj, root);
    
    dominating_number_rec(tree.get(), a, b);
    
    return a[root];
}
