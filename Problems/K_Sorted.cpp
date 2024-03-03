#include <iterator>
#include <random>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

/// K-sorted problem------------------------------------------------

/// This method generate almost sorted sequence, such that every   |
/// value is at most 'k' positions away from it's final position,  |
/// that it will have after sorting the sequence.                  |
template< typename RanIt >
void generate_k_sorted(RanIt begin, RanIt end, int k)
{
    if (std::distance(begin, end) <= 1)
        return;  // 1-length sequence is always sorted
    // Sort initially
    std::sort(begin, end);
    // Prepare random numbers generator
    std::default_random_engine gen;
    std::uniform_int_distribution< int > dist(0, 1);
    // Adjacent swaps 'k' times
    while (k--) {
        for (RanIt it1 = begin, it2 = std::next(begin);
            it2 != end;
            ++it1, ++it2) {
            if (dist(gen)) {
                std::iter_swap(it1, it2);
                // Advance once more, so same value will not be 
                // swapped again
                ++it1;
                ++it2;
                if (it2 == end)
                    break;
            }
        }
    }
}


/// Sorts given sequence [begin, end), considering that each value | 
/// is at most 'k' positions away from it's final place, that it   |
/// will have after sorting.                                       |
template< typename RanIt >
void k_sort(RanIt begin, RanIt end, int k)
{
    typedef typename std::iterator_traits< RanIt >::value_type value_type;
    // Prepare the min-heap
    std::priority_queue<
        value_type,
        std::vector< value_type >,
        std::greater< value_type > > heap;
    RanIt in = begin, out = begin;
    // Push first 'k' values into the heap
    for (int i = 0;
        i < k && in != end;
        ++i, ++in)
        heap.push(*in);
    // Process sliding window
    while (in != end) {
        heap.push(*(in++));
        *(out++) = heap.top();
        heap.pop();
    }
    // Empty the heap
    while (!heap.empty()) {
        *(out++) = heap.top();
        heap.pop();
    }
    assert(out == end);
}


/// Prints values in range [begin, end) to the screen.             |
template< typename InIt >
void print_sequence(InIt begin, InIt end)
{
    std::cout << " [";
    for (InIt it = begin; it != end; ++it)
        std::cout << " " << *it;
    std::cout << " ]" << std::endl;
}

int main()
{
    std::vector<int> vec{ 6,1,8,2,3,5,4,8,6,4,596,4,532,6,51,32,652,165,16,51 };
    generate_k_sorted(vec.begin(), vec.end(), 4);
    std::cout << "K sorted: ";
    for (auto i : vec)
        std::cout << i << " ";


    std::cout << "\n  Sorted: ";
    k_sort(vec.begin(), vec.end(), 4);
    for (auto i : vec)
        std::cout << i << " ";

}