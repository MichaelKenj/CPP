#include <iostream>
#include <deque>
#include <array>
#include <vector>

using VECTOR_ITERATOR = std::vector<int>::iterator;
using DEQUE_ITERATOR = std::deque<int>::iterator;

// 12 can be replaced by any other integer
using ARRAY_ITERATOR = std::array<int, 12>::iterator;


template <typename Iterator>
bool isContainerSorted(Iterator begin, Iterator end)
{
    for (auto it = begin; it != end - 1; ++it)
    {
        if (*it > *(it + 1))
            return false;
    }
    return true;
}

template <typename Iterator>
Iterator binarySearch(Iterator begin, Iterator end, typename std::iterator_traits<Iterator>::value_type value)
{
    // Check, is container sorted
    if (!isContainerSorted(begin, end))
        throw std::logic_error("Container isn't sorted to complete binary search");

    Iterator end_not_found = end;

    if (*begin == value)
        return begin;
    if (*(end - 1) == value)
        return end - 1;

    // Binary search
    while (begin < end)
    {
        Iterator mid = begin + (end - begin) / 2;

        if (*mid < value)
            begin = mid + 1;
        else if (*mid > value)
            end = mid;
        else
            return mid;
    }

    return end_not_found;
}

int main()
{
    // Usage with vector
    std::vector<int> vec{ -56421,-32554, -6547, -254, 12, 65, 987, 987, 1026, 1235, 56462, 5674985 };

    std::cout << "EXAMPLE WITH VECTOR(EXISTING VALUE)\n";
    int value = 1235;
    VECTOR_ITERATOR vec_res = binarySearch(vec.begin(), vec.end(), value);
    if (vec_res == vec.end())
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << *vec_res << std::endl;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH VECTOR(NOT EXISTING VALUE)\n";
    value = 1345;
    vec_res = binarySearch(vec.begin(), vec.end(), value);
    if (vec_res == vec.end())
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << *vec_res << std::endl;

    std::cout << std::endl;

    // Usage with deque
    std::deque<int> deq{ -56421,-32554, -6547, -254, 12, 65, 987, 987, 1026, 1235, 56462, 5674985 };

    std::cout << "EXAMPLE WITH DEQUE(EXISTING VALUE)\n";
    value = 1235;
    DEQUE_ITERATOR deq_res = binarySearch(deq.begin(), deq.end(), value);
    if (deq_res == deq.end())
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << *deq_res << std::endl;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH DEQUE(NOT EXISTING VALUE)\n";
    value = 1345;
    deq_res = binarySearch(deq.begin(), deq.end(), value);
    if (deq_res == deq.end())
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << *deq_res;

    std::cout << std::endl;

    // Usage with array
    std::array<int, 12> arr{ -56421,-32554, -6547, -254, 12, 65, 987, 987, 1026, 1235, 56462, 5674985 };

    std::cout << "EXAMPLE WITH ARRAY(EXISTING VALUE)\n";
    value = 1235;
    ARRAY_ITERATOR arr_res = binarySearch(arr.begin(), arr.end(), value);
    if (arr_res == arr.end())
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << *arr_res << std::endl;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH ARRAY(NOT EXISTING VALUE)\n";
    value = 1345;
    arr_res = binarySearch(arr.begin(), arr.end(), value);
    if (arr_res == arr.end())
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << *arr_res;

}