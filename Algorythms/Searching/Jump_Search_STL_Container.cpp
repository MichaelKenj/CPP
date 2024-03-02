#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <deque>
#include <array>

template <typename Container>
int jumpSearch(const Container& container, typename Container::value_type& x, int n)
{
    // Finding block size to be jumped
    int step = std::sqrt(n);

    typename Container::value_type prev = 0;
    while (container[std::min(step, n) - 1] < x)
    {
        prev = step;
        step += std::sqrt(n);
        if (prev >= n)
            return -1;
    }

    // Doing a linear search for x in block
    // beginning with prev.
    while (container[prev] < x)
    {
        prev++;

        // If we reached next block or end of
        // array, element is not present.
        if (prev == std::min(step, n))
            return -1;
    }
    // If element is found
    if (container[prev] == x)
        return prev;

    return -1;
}

// Driver program to test function
int main()
{
    // Usage with vector
    std::vector<int> vec{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };

    std::cout << "EXAMPLE WITH VECTOR(EXISTING VALUE)\n";
    int value = 55;
    int vec_res = jumpSearch(vec, value, vec.size());
    if (vec_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Number " << value << " is at index " << vec_res;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH VECTOR(NOT EXISTING VALUE)\n";
    value = 1345;
    vec_res = jumpSearch(vec, value, vec.size());
    if (vec_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Number " << value << " is at index " << vec_res;

    std::cout << std::endl;

    // Usage with deque
    std::deque<int> deq{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };

    std::cout << "EXAMPLE WITH DEQUE(EXISTING VALUE)\n";
    value = 55;
    std::size_t deq_res = jumpSearch(vec, value, vec.size());
    if (deq_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Number " << value << " is at index " << deq_res;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH DEQUE(NOT EXISTING VALUE)\n";
    value = 1345;
    deq_res = jumpSearch(vec, value, vec.size());
    if (deq_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Number " << value << " is at index " << deq_res;

    std::cout << std::endl;

    // Usage with array
    std::array<int, 16> arr{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };

    std::cout << "EXAMPLE WITH ARRAY(EXISTING VALUE)\n";
    value = 55;
    int arr_res = jumpSearch(vec, value, vec.size());
    if (arr_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Number " << value << " is at index " << arr_res;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH ARRAY(NOT EXISTING VALUE)\n";
    value = 1345;
    arr_res = jumpSearch(vec, value, vec.size());
    if (arr_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Number " << value << " is at index " << arr_res;


    
    return 0;
}