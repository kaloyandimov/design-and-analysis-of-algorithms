//
//  algorithm.cpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 12.04.24.
//

#include "algorithm.hpp"

#include <limits.h>

#include "heap.hpp"
#include "utility.hpp"

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = key;
    }
}

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[i]) {
                swap(arr[j], arr[i]);
            }
        }
    }
}

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                
                swapped = true;
            }
        }
        
        if (!swapped) {
            break;
        }
    }
}

void merge(int arr[], int l, int mid, int h) {
    int n = mid - l + 1;
    int m = h - mid;
    
    int* lhs = new int[n + 1];
    int* rhs = new int[m + 1];
    
    copy(arr + l, n, lhs);
    copy(arr + mid + 1, m, rhs);
    
    lhs[n] = INT_MAX;
    rhs[m] = INT_MAX;
    
    int i = 0;
    int j = 0;
    
    for (int k = l; k <= h; k++) {
        if (lhs[i] <= rhs[j]) {
            arr[k] = lhs[i];
            i++;
        } else {
            arr[k] = rhs[j];
            j++;
        }
    }
    
    delete[] lhs;
    delete[] rhs;
}

void merge_sort(int arr[], int l, int h) {
    if (l >= h) {
        return;
    }
    
    int mid = l + (h - l) / 2;
    
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, h);
    merge(arr, l, mid, h);
}

void merge_sort(int arr[], int n) {
    merge_sort(arr, 0, n);
}

int partition(int arr[], int l, int h) {
    int pivot = arr[h - 1];
    int pp = l;
    
    for (int i = l; i < h; i++) {
        if (arr[i] < pivot) {
            swap(arr[i], arr[pp]);
            pp++;
        }
    }
    
    swap(arr[pp], arr[h - 1]);
    
    return pp;
}

void quicksort(int arr[], int l, int h) {
    if (l >= h) {
        return;
    }
    
    int mid = partition(arr, l, h);
    
    quicksort(arr, l, mid);
    quicksort(arr, mid + 1, h);
}

void quicksort(int arr[], int n) {
    quicksort(arr, 0, n);
}

void heap_sort(int arr[], int n) {
    build_heap(arr, n);
    
    for (int i = n - 1; !is_root(i); i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void counting_sort(int arr[], int n, int k) {
    int* count = new int[k + 1]{};
    int* result = new int[n];
    
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    
    for (int i = 1; i < k + 1; i++) {
        count[i] += count[i - 1];
    }
    
    for (int i = n - 1; i >= 0; i--) {
        result[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    
    copy(result, n, arr);
    
    delete[] result;
    delete[] count;
}
