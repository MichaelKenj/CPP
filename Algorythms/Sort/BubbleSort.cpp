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

/// BUBBLE SORT with ITERATORS------------------------------------------------------------------------------------
template <typename Iterator, typename Compare = std::less<typename std::iterator_traits<Iterator>::value_type>>
void bubbleSort(Iterator begin, Iterator end, Compare compare = Compare())
{
    for (auto i = begin; i != end; ++i)
    {
        for (auto j = std::next(i); j != end; ++j)
        {
            if (compare(*j, *i))
                std::swap(*i, *j);
        }
    }
}

/// BUBBLE SORT with ITERATORS------------------------------------------------------------------------------------

/// BUBBLE SORT with INDEXES--------------------------------------------------------------------------------------
template <typename Container, typename Compare = std::less<typename Container::value_type>>
void bubbleSort(Container& container, std::size_t begin, std::size_t end, Compare compare = Compare())
{

    bool swapped;
    for (std::size_t i = begin; i <= end - 1; ++i) {
        swapped = false;
        for (std::size_t j = begin; j <= end - i - 1; ++j) {
            if (compare (container[j + 1], container[j])) {
                std::swap(container[j], container[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}
/// BUBBLE SORT with INDEXES--------------------------------------------------------------------------------------


int main()
{
    // Usage with VECTOR
    std::vector<int> VEC_WITH_INDEX{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    bubbleSort(VEC_WITH_INDEX, 0, VEC_WITH_INDEX.size() - 1);
    //bubbleSort(VEC_WITH_INDEX, 0, VEC_WITH_INDEX.size() - 1, std::greater<int>());
    std::cout << GET_VARIABLE_NAME(VEC_WITH_INDEX) << ": ";
    print(VEC_WITH_INDEX);



    std::vector<int> VEC_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    bubbleSort(VEC_WITH_ITERATOR.begin(), VEC_WITH_ITERATOR.end());
    //bubbleSort(VEC_WITH_ITERATOR.begin(), VEC_WITH_ITERATOR.end(), std::greater<int>());
    std::cout << GET_VARIABLE_NAME(VEC_WITH_ITERATOR) << ": ";
    print(VEC_WITH_ITERATOR);



    // Usage with DEQUE
    std::deque<int> DEQUE_WITH_INDEX{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    bubbleSort(DEQUE_WITH_INDEX, 0, DEQUE_WITH_INDEX.size() - 1);
    //bubbleSort(DEQUE_WITH_INDEX, 0, DEQUE_WITH_INDEX.size() - 1, std::greater<int>());
    std::cout << GET_VARIABLE_NAME(DEQUE_WITH_INDEX) << ": ";
    print(DEQUE_WITH_INDEX);



    std::deque<int> DEQUE_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    bubbleSort(DEQUE_WITH_ITERATOR.begin(), DEQUE_WITH_ITERATOR.end());
    //bubbleSort(DEQUE_WITH_ITERATOR.begin(), DEQUE_WITH_ITERATOR.end(), std::greater<int>());
    std::cout << GET_VARIABLE_NAME(DEQUE_WITH_ITERATOR) << ": ";
    print(DEQUE_WITH_ITERATOR);



    // Usage with LIST
    std::list<int> LIST_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    bubbleSort(LIST_WITH_ITERATOR.begin(), LIST_WITH_ITERATOR.end());
    //bubbleSort(LIST_WITH_ITERATOR.begin(), LIST_WITH_ITERATOR.end(), std::greater<int>());
    std::cout << GET_VARIABLE_NAME(LIST_WITH_ITERATOR) << ": ";
    print(LIST_WITH_ITERATOR);



    // Usage with ARRAY
    std::array<int, 13> ARRAY_WITH_INDEX{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    bubbleSort(ARRAY_WITH_INDEX, 0,  ARRAY_WITH_INDEX.size() - 1);
    //bubbleSort(ARRAY_WITH_INDEX, 0,  ARRAY_WITH_INDEX.size() - 1, std::greater<int>());
    std::cout << GET_VARIABLE_NAME(ARRAY_WITH_INDEX) << ": ";
    print(ARRAY_WITH_INDEX);



    // Usage with ARRAY
    std::array<int, 13> ARRAY_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    bubbleSort(ARRAY_WITH_ITERATOR.begin(), ARRAY_WITH_ITERATOR.end());
    //bubbleSort(ARRAY_WITH_ITERATOR.begin(), ARRAY_WITH_ITERATOR.end(), std::greater<int>());
    std::cout << GET_VARIABLE_NAME(ARRAY_WITH_ITERATOR) << ": ";
    print(ARRAY_WITH_ITERATOR);
}