//
//  heap.cpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 13.04.24.
//

#include "heap.hpp"
#include "utility.hpp"

int left(int i) {
    return i * 2 + 1;
}

int right(int i) {
    return i * 2 + 2;
}

int level(int i) {
    int level = 0;
    
    while (i >>= 1) {
        level++;
    }
    
    return level;
}

int parent(int i) {
    return (i - 1) / 2;
}

bool is_root(int i) {
    return i == 0;
}

bool is_leaf(int i, int n) {
    return i >= n / 2;
}

bool is_internal_vertex(int i, int n) {
    return !is_leaf(i, n);
}

bool is_heap(int arr[], int n) {
    for (int i = 0; is_internal_vertex(i, n); i++) {
        int l = left(i);
        int r = right(i);

        if (arr[l] > arr[i]) {
            return false;
        }

        if (r < n && arr[r] > arr[i]) {
            return false;
        }
    }

    return true;
}

void heapify(int arr[], int n, int i) {
    while (is_internal_vertex(i, n)) {
        int largest = i;
        int l = left(i);
        int r = right(i);

        if (arr[l] > arr[largest]) {
            largest = l;
        }
        if (r < n && arr[r] > arr[largest]) {
            largest = r;
        }
        if (largest == i) {
            break;
        }

        swap(arr[i], arr[largest]);
        
        i = largest;
    }
}

void build_heap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

void heap_sort(int arr[], int n) {
    build_heap(arr, n);
    
    for (int i = n - 1; !is_root(i); i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
