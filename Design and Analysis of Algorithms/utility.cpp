//
//  utility.cpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 9.04.24.
//

#include "utility.hpp"

#include <iostream>

void swap(int& x, int& y) {
    int z = x;
    x = y;
    y = z;
}

void print(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
}
