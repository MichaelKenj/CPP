#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <forward_list>
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


/// MERGE SORT with ITERATORS--------------------------------------------------------------------------------
template <typename _RandAccIt, typename Compare = std::less<typename std::iterator_traits<_RandAccIt>::value_type>>
void merge(_RandAccIt begin, _RandAccIt mid, _RandAccIt end, Compare compare = Compare())
{
    using ValueType = typename std::iterator_traits<_RandAccIt>::value_type;

    std::vector<ValueType> merged;

    _RandAccIt leftSubArrIter = begin;
    _RandAccIt rightSubArrIter = mid;

    while (leftSubArrIter != mid && rightSubArrIter != end)
    {
        merged.push_back((compare(*leftSubArrIter, *rightSubArrIter))
            ? *leftSubArrIter++ : *rightSubArrIter++);
    }

    while (leftSubArrIter != mid)
    {
        merged.push_back(*leftSubArrIter++);
    }

    while (rightSubArrIter != end)
    {
        merged.push_back(*rightSubArrIter++);
    }

    std::copy(merged.begin(), merged.end(), begin);
}

template <typename _RandAccIt, typename Compare = std::less<typename std::iterator_traits<_RandAccIt>::value_type>>
void mergeSort(_RandAccIt begin, _RandAccIt end, Compare compare = Compare())
{
    auto size = std::distance(begin, end);
    if (size < 2)
        return;

    auto middle = std::next(begin, size / 2);

    // Pass the comparator to recursive calls
    mergeSort(begin, middle, compare);
    mergeSort(middle, end, compare);

    // Pass the comparator to the merge function
    merge(begin, middle, end, compare);
}
/// MERGE SORT with ITERATORS--------------------------------------------------------------------------------

int main()
{
    // Usage with VECTOR
    std::vector<int> VEC_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    mergeSort(VEC_WITH_ITERATOR.begin(), VEC_WITH_ITERATOR.end());
    //mergeSort(VEC_WITH_ITERATOR.begin(), VEC_WITH_ITERATOR.end(), std::greater<int>());
    std::cout << GET_VARIABLE_NAME(VEC_WITH_ITERATOR) << ": ";
    print(VEC_WITH_ITERATOR);



    // Usage with DEQUE
    std::deque<int> DEQUE_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    mergeSort(DEQUE_WITH_ITERATOR.begin(), DEQUE_WITH_ITERATOR.end());
    //mergeSort(DEQUE_WITH_ITERATOR.begin(), DEQUE_WITH_ITERATOR.end(), std::greater<int>());
    std::cout << GET_VARIABLE_NAME(DEQUE_WITH_ITERATOR) << ": ";
    print(DEQUE_WITH_ITERATOR);



    // Usage with LIST
    std::list<int> LIST_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    mergeSort(LIST_WITH_ITERATOR.begin(), LIST_WITH_ITERATOR.end());
    //mergeSort(LIST_WITH_ITERATOR.begin(), LIST_WITH_ITERATOR.end(), std::greater<int>());
    std::cout << GET_VARIABLE_NAME(LIST_WITH_ITERATOR) << ": ";
    print(LIST_WITH_ITERATOR);



    // Usage with ARRAY
    std::array<int, 13> ARRAY_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    mergeSort(ARRAY_WITH_ITERATOR.begin(), ARRAY_WITH_ITERATOR.end());
    //mergeSort(ARRAY_WITH_ITERATOR.begin(), ARRAY_WITH_ITERATOR.end(), std::greater<int>());
    std::cout << GET_VARIABLE_NAME(ARRAY_WITH_ITERATOR) << ": ";
    print(ARRAY_WITH_ITERATOR);
}