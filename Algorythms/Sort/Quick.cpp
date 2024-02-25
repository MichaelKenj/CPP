#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <deque>
#include <list>

/// Gets variable name (for beautiful print)
#define GET_VARIABLE_NAME(Variable) (#Variable)

template <typename Container>
void print(const Container& container)
{
    for (auto i : container)
        std::cout << i << " ";
    std::cout << std::endl;

}


/// QUICK SORT with ITERATORS----------------------------------------------------------
template <typename RandomIt, typename Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
RandomIt Partition(RandomIt first, RandomIt last, Compare compare = Compare())
{
    auto pivot = std::prev(last, 1);
    auto i = first;

    for (auto j = first; j != pivot; ++j) {
        if (compare(*j, *pivot)) {
            std::swap(*i++, *j);
        }
    }

    std::swap(*i, *pivot);
    return i;
}

template <typename RandomIt, typename Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
void quickSort(RandomIt first, RandomIt last, Compare compare = Compare())
{
    if (std::distance(first, last) > 1) {
        RandomIt bound = Partition(first, last, compare);

        quickSort(first, bound, compare);
        quickSort(std::next(bound), last, compare);
    }
}
/// QUICK SORT with ITERATORS----------------------------------------------------------




/// QUICK SORT with INDEXES------------------------------------------------------------
template <typename Container, typename Compare = std::less<typename Container::value_type>>
std::size_t partition(Container& container, int low, int high, Compare compare = Compare())
{
    int pivot = container[high];
    std::size_t i = low - 1;

    for (std::size_t j = low; j <= high; ++j)
    {
        if (compare(container[j], pivot))
        {
            ++i;
            std::swap(container[i], container[j]);
        }
    }
    std::swap(container[i + 1], container[high]);
    return i + 1;
}

template <typename Container, typename Compare = std::less<typename Container::value_type>>
void quickSort(Container& container, int low, int high, Compare compare = Compare())
{
    if (low < high)
    {
        std::size_t p = partition(container, low, high, compare);

        quickSort(container, low, p - 1, compare);
        quickSort(container, p + 1, high, compare);

    }
}
/// QUICK SORT with INDEXES------------------------------------------------------------

int main()
{
    // Usage with VECTOR
    std::vector<int> VEC_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    quickSort(VEC_WITH_ITERATOR.begin(), VEC_WITH_ITERATOR.end());
    //quickSort(VEC_WITH_ITERATOR.begin(), VEC_WITH_ITERATOR.end(), std::greater<int>());
    std::cout << GET_VARIABLE_NAME(VEC_WITH_ITERATOR) << ": ";
    print(VEC_WITH_ITERATOR);

    std::vector<int> VEC_WITH_INDEX{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    quickSort(VEC_WITH_INDEX, 0, VEC_WITH_INDEX.size() - 1);
    //quickSort(VEC_WITH_INDEX, 0, VEC_WITH_INDEX.size() - 1, std::greater<int>());
    std::cout << GET_VARIABLE_NAME(VEC_WITH_INDEX) << ": ";
    print(VEC_WITH_INDEX);

    // Usage with DEQUE
    std::deque<int> DEQUE_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    quickSort(DEQUE_WITH_ITERATOR.begin(), DEQUE_WITH_ITERATOR.end());
    //quickSort(DEQUE_WITH_ITERATOR.begin(), DEQUE_WITH_ITERATOR.end(), std::greater<int>());
    std::cout << GET_VARIABLE_NAME(DEQUE_WITH_ITERATOR) << ": ";
    print(DEQUE_WITH_ITERATOR);

    std::deque<int> DEQUE_WITH_INDEX{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    quickSort(DEQUE_WITH_INDEX, 0, DEQUE_WITH_INDEX.size() - 1);
    //quickSort(DEQUE_WITH_INDEX, 0, DEQUE_WITH_INDEX.size() - 1, std::greater<int>());
    std::cout << GET_VARIABLE_NAME(DEQUE_WITH_INDEX) << ": ";
    print(DEQUE_WITH_INDEX);

    // Usage with LIST
    std::list<int> LIST_WITH_ITERATOR{ 9, 10, 5, 3, 20, -7, 2, 19, 64, 21, 0, 8, 7 };
    quickSort(LIST_WITH_ITERATOR.begin(), LIST_WITH_ITERATOR.end());
    std::cout << GET_VARIABLE_NAME(LIST_WITH_ITERATOR) << ": ";
    print(LIST_WITH_ITERATOR);

  

    return 0;
}
