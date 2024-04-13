//
//  heap.hpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 13.04.24.
//

#ifndef heap_hpp
#define heap_hpp

int left(int i);

int right(int i);

int level(int i);

int parent(int i);

bool is_root(int i);

bool is_leaf(int i, int n);

bool is_internal_vertex(int i, int n);

bool is_heap(int arr[], int n);

void heapify(int arr[], int n, int i);

void build_heap(int arr[], int n);

#endif /* heap_hpp */
