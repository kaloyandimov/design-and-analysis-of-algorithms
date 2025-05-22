//
//  helper.hpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 17.05.25.
//

#ifndef helper_hpp
#define helper_hpp

#include <ostream>
#include <random>
#include <vector>

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    for (const auto& x : v) {
        out << x << ' ';
    }
    
    return out;
}

template <class T>
T get_random_number(T n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> distrib(0, n);
    
    return distrib(gen);
}

#endif /* helper_hpp */
