//
//  tree.hpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 17.05.25.
//

#ifndef tree_hpp
#define tree_hpp

#include <memory>
#include <vector>

#include "graph.hpp"

struct TreeNode {
    explicit TreeNode(int x);
    
    std::vector<std::unique_ptr<TreeNode>> children;
    int data;
};

std::unique_ptr<TreeNode> build_rooted_tree(const AdjacencyList& adj, int s);

int independence_number(const AdjacencyList& adj);

int vertex_cover_size(const AdjacencyList& adj);

int dominating_number(const AdjacencyList& adj);

#endif /* tree_hpp */
