#include<iostream>
#include <vector>
#include <array>
#include <deque>



template <typename Container>
int interpolationSearch(const Container& container, typename Container::value_type n, typename Container::value_type x)
{
    // Find indexes of two corners
    int low = 0, high = (n - 1);
    // Since array is sorted, an element present
    // in array must be in range defined by corner

    while (low <= high && x >= container[low] && x <= container[high])
    {
        if (low == high)
        {
            if (container[low] == x) 
                return low;
            return -1;
        }
        // Probing the position with keeping
        // uniform distribution in mind.
        int pos = low + (((double)(high - low) /
            (container[high] - container[low])) * (x - container[low]));

        // Condition of target found
        if (container[pos] == x)
            return pos;
        // If x is larger, x is in upper part
        if (container[pos] < x)
            low = pos + 1;
        // If x is smaller, x is in the lower part
        else
            high = pos - 1;
    }
    return -1;
}

// Main function
int main()
{
    // Usage with vector
    std::vector<int> vec{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };

    std::cout << "EXAMPLE WITH VECTOR(EXISTING VALUE)\n";
    int value = 55;
    int vec_res = interpolationSearch(vec, vec.size(), value);
    if (vec_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Number " << value << " is at index " << vec_res;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH VECTOR(NOT EXISTING VALUE)\n";
    value = 1345;
    vec_res = interpolationSearch(vec, vec.size(), value);
    if (vec_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Number " << value << " is at index " << vec_res;

    std::cout << std::endl;

    // Usage with deque
    std::deque<int> deq{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };

    std::cout << "EXAMPLE WITH DEQUE(EXISTING VALUE)\n";
    value = 55;
    std::size_t deq_res = interpolationSearch(deq, deq.size(), value);
    if (deq_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Number " << value << " is at index " << deq_res;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH DEQUE(NOT EXISTING VALUE)\n";
    value = 1345;
    deq_res = interpolationSearch(deq, deq.size(), value);
    if (deq_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Number " << value << " is at index " << deq_res;

    std::cout << std::endl;

    // Usage with array
    std::array<int, 16> arr{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };

    std::cout << "EXAMPLE WITH ARRAY(EXISTING VALUE)\n";
    value = 55;
    int arr_res = interpolationSearch(arr, arr.size(), value);
    if (arr_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Number " << value << " is at index " << arr_res;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH ARRAY(NOT EXISTING VALUE)\n";
    value = 1345;
    arr_res = interpolationSearch(arr, arr.size(), value);
    if (arr_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Number " << value << " is at index " << arr_res;

    return 0;
}