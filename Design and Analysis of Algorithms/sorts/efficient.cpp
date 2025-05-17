//
//  efficient.cpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 16.05.25.
//

#include <climits>

#include "efficient.hpp"
#include "utility.hpp"

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
    merge_sort(arr, 0, n - 1);
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

void quick_sort(int arr[], int l, int h) {
    if (l >= h) {
        return;
    }
    
    int mid = partition(arr, l, h);
    
    quick_sort(arr, l, mid);
    quick_sort(arr, mid + 1, h);
}

void quick_sort(int arr[], int n) {
    quick_sort(arr, 0, n);
}
