//
//  helper.hpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 17.05.25.
//

#ifndef helper_hpp
#define helper_hpp

#include <ostream>
#include <vector>

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    for (const auto& x : v) {
        out << x << ' ';
    }
    
    return out;
}

#endif /* helper_hpp */
