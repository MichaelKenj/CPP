#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <deque>
#include <list>
#include <array>

/// Gets variable name (for beautiful print)
#define GET_VARIABLE_NAME(Variable) (#Variable)

template <typename Container>
void print(const Container& container)
{
    for (auto i : container)
        std::cout << i << " ";
    std::cout << std::endl;

}


/// INSERTION SORT with ITERATORS----------------------------------------------------------
template <typename RandomIt, typename Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
void insertionSort(RandomIt begin, RandomIt end, Compare compare = Compare())
{
    for (auto it = std::next(begin); it != end; ++it) {
        auto key = *it;
        auto jt = it;

        while (jt != begin && compare(key, *std::prev(jt))) {
            *jt = *std::prev(jt);
            --jt;
        }

        *jt = key;
    }
}
/// INSERTION SORT with ITERATORS----------------------------------------------------------




/// INSERTION SORT with INDEXES------------------------------------------------------------
template <typename Container, typename Compare = std::less<typename Container::value_type>>
void insertionSort(Container& container, int low, int high, Compare compare = Compare())
{
    for (int i = low + 1; i <= high; ++i) {
        auto key = container[i];
        int j = i - 1;

        while (j >= low && compare(key, container[j])) {
            container[j + 1] = container[j];
            --j;
        }

        container[j + 1] = key;
    }
}
/// INSERTION SORT with INDEXES------------------------------------------------------------

int main()
{
    // Usage with VECTOR
    std::vector<int> VEC_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    insertionSort(VEC_WITH_ITERATOR.begin(), VEC_WITH_ITERATOR.end());
    //insertionSort(VEC_WITH_ITERATOR.begin(), VEC_WITH_ITERATOR.end(), std::greater<int>());
    std::cout << GET_VARIABLE_NAME(VEC_WITH_ITERATOR) << ": ";
    print(VEC_WITH_ITERATOR);

    std::vector<int> VEC_WITH_INDEX{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    insertionSort(VEC_WITH_INDEX, 0, VEC_WITH_INDEX.size() - 1);
    //insertionSort(VEC_WITH_INDEX, 0, VEC_WITH_INDEX.size() - 1, std::greater<int>());
    std::cout << GET_VARIABLE_NAME(VEC_WITH_INDEX) << ": ";
    print(VEC_WITH_INDEX);

    // Usage with DEQUE
    std::deque<int> DEQUE_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    insertionSort(DEQUE_WITH_ITERATOR.begin(), DEQUE_WITH_ITERATOR.end());
    //insertionSort(DEQUE_WITH_ITERATOR.begin(), DEQUE_WITH_ITERATOR.end(), std::greater<int>());
    std::cout << GET_VARIABLE_NAME(DEQUE_WITH_ITERATOR) << ": ";
    print(DEQUE_WITH_ITERATOR);

    std::deque<int> DEQUE_WITH_INDEX{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    insertionSort(DEQUE_WITH_INDEX, 0, DEQUE_WITH_INDEX.size() - 1);
    //insertionSort(DEQUE_WITH_INDEX, 0, DEQUE_WITH_INDEX.size() - 1, std::greater<int>());
    std::cout << GET_VARIABLE_NAME(DEQUE_WITH_INDEX) << ": ";
    print(DEQUE_WITH_INDEX);

    // Usage with LIST
    std::list<int> LIST_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    insertionSort(LIST_WITH_ITERATOR.begin(), LIST_WITH_ITERATOR.end());
    std::cout << GET_VARIABLE_NAME(LIST_WITH_ITERATOR) << ": ";
    print(LIST_WITH_ITERATOR);

    // Usage with ARRAY
    std::array<int, 13> ARRAY_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    insertionSort(ARRAY_WITH_ITERATOR.begin(), ARRAY_WITH_ITERATOR.end());
    //insertionSort(ARRAY_WITH_ITERATOR.begin(), ARRAY_WITH_ITERATOR.end(), std::greater<int>());
    std::cout << GET_VARIABLE_NAME(ARRAY_WITH_ITERATOR) << ": ";
    print(ARRAY_WITH_ITERATOR);

    std::array<int, 13> ARRAY_WITH_INDEX{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    insertionSort(ARRAY_WITH_INDEX, 0, ARRAY_WITH_INDEX.size() - 1);
    //insertionSort(ARRAY_WITH_INDEX, 0, ARRAY_WITH_INDEX.size() - 1, std::greater<int>());
    std::cout << GET_VARIABLE_NAME(ARRAY_WITH_INDEX) << ": ";
    print(ARRAY_WITH_INDEX);



    return 0;
}