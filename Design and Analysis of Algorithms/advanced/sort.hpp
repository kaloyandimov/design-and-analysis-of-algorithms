//
//  sort.hpp
//  Design and Analysis of Algorithms
//
//  Created by Kaloyan Dimov on 23.04.24.
//

#ifndef sort_hpp
#define sort_hpp

#include <algorithm>
#include <functional>
#include <iterator>

template <class ForwardIt, class Compare>
void insertion_sort(ForwardIt first, ForwardIt last, Compare comp);

template <class ForwardIt>
void insertion_sort(ForwardIt first, ForwardIt last);

template <class ForwardIt, class Compare>
void selection_sort(ForwardIt first, ForwardIt last, Compare comp);

template <class ForwardIt>
void selection_sort(ForwardIt first, ForwardIt last);

template <class ForwardIt, class Compare>
void bubble_sort(ForwardIt first, ForwardIt last, Compare comp);

template <class ForwardIt>
void bubble_sort(ForwardIt first, ForwardIt last);

template<class ForwardIt, class Compare>
void merge_sort(ForwardIt first, ForwardIt last, Compare comp);

template<class ForwardIt>
void merge_sort(ForwardIt first, ForwardIt last);

template <class ForwardIt, class Compare>
void quick_sort(ForwardIt first, ForwardIt last, Compare comp);

template <class ForwardIt>
void quick_sort(ForwardIt first, ForwardIt last);

template <class ForwardIt, class Compare>
void heap_sort(ForwardIt first, ForwardIt last, Compare comp);

template <class ForwardIt>
void heap_sort(ForwardIt first, ForwardIt last);

template <class ForwardIt, class Compare>
void selection_sort(ForwardIt first, ForwardIt last, Compare comp) {
    for (auto it = first; it != last; ++it) {
        std::iter_swap(it, std::min_element(it, last, comp));
    }
}

template <class ForwardIt>
void selection_sort(ForwardIt first, ForwardIt last) {
    selection_sort(first, last, std::less<typename std::iterator_traits<ForwardIt>::value_type>());
}

template <typename ForwardIt, class Compare>
void bubble_sort(ForwardIt first, ForwardIt last, Compare comp) {
    for (auto sorted = first; first != last; last = sorted) {
        sorted = first;
        
        for (auto curr = first, prev = first; std::next(curr) != last; ++prev) {
            if (comp(*curr, *prev)) {
                std::iter_swap(curr, prev);
                sorted = curr;
            }
        }
    }
}

template <class ForwardIt>
void bubble_sort(ForwardIt first, ForwardIt last) {
    bubble_sort(first, last, std::less<typename std::iterator_traits<ForwardIt>::value_type>());
}

template <class ForwardIt, class Compare>
void insertion_sort(ForwardIt first, ForwardIt last, Compare comp) {
    for (auto it = first; it != last; ++it) {
        std::rotate(std::upper_bound(first, it, *it, comp), it, std::next(it));
    }
}

template <class ForwardIt>
void insertion_sort(ForwardIt first, ForwardIt last) {
    insertion_sort(first, last, std::less<typename std::iterator_traits<ForwardIt>::value_type>());
}

template<class ForwardIt, class Compare>
void merge_sort(ForwardIt first, ForwardIt last, Compare comp) {
    if (first == last) {
        return;
    }
    
    auto middle = std::next(first, std::distance(first, last) / 2);
    
    merge_sort(first, middle, comp);
    merge_sort(middle, last, comp);
    
    std::inplace_merge(first, middle, last, comp);
}

template <class ForwardIt>
void merge_sort(ForwardIt first, ForwardIt last) {
    merge_sort(first, last, std::less<typename std::iterator_traits<ForwardIt>::value_type>());
}

template <class ForwardIt, class Compare>
void quick_sort(ForwardIt first, ForwardIt last, Compare comp) {
    if (first == last) {
        return;
    }
    
    auto pivot = *std::next(first, std::distance(first, last) / 2);
    auto middle1 = std::partition(first, last, [&](const auto& em) {
        return comp(em, pivot);
    });
    auto middle2 = std::partition(middle1, last, [&](const auto& em) {
        return !comp(em, pivot);
    });
    
    quick_sort(first, middle1, comp);
    quick_sort(middle2, last, comp);
}

template <class ForwardIt>
void quick_sort(ForwardIt first, ForwardIt last) {
    quick_sort(first, last, std::less<typename std::iterator_traits<ForwardIt>::value_type>());
}

template <class ForwardIt, class Compare>
void heap_sort(ForwardIt first, ForwardIt last, Compare comp) {
    std::make_heap(first, last, comp);
    std::sort_heap(first, last, comp);
}

template <class ForwardIt>
void heap_sort(ForwardIt first, ForwardIt last) {
    heap_sort(first, last, std::less<typename std::iterator_traits<ForwardIt>::value_type>());
}

#endif /* sort_hpp */
