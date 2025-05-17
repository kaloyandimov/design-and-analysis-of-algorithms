//
//  distribution.cpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 16.05.25.
//

#include "distribution.hpp"
#include "utility.hpp"

void counting_sort(int arr[], int n, int k) {
    int* count = new int[k + 1]{0};
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
