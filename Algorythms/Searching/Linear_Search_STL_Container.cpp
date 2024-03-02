#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <array>

using VECTOR_ITERATOR = std::vector<int>::iterator;
using DEQUE_ITERATOR = std::deque<int>::iterator;
using LIST_ITERATOR = std::list<int>::iterator;

// 12 can be replaced by any other integer
using ARRAY_ITERATOR = std::array<int, 12>::iterator;

template <typename Iterator>
Iterator linearSearch(Iterator begin, Iterator end, const typename std::iterator_traits<Iterator>::value_type& value)
{
	if (*begin == value)
		return begin;
	while (begin != end)
	{
		if (*begin == value)
			return begin;
		begin = std::next(begin);
	}
	return end;

}

void example_with_iterator()
{
    // Usage with vector
    std::vector<int> vec{ -56421,-32554, -6547, -254, 12, 65, 987, 987, 1026, 1235, 56462, 5674985 };

    std::cout << "EXAMPLE WITH VECTOR(EXISTING VALUE)\n";
    int value = 1235;
    VECTOR_ITERATOR vec_res = linearSearch(vec.begin(), vec.end(), value);
    if (vec_res == vec.end())
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << *vec_res << std::endl;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH VECTOR(NOT EXISTING VALUE)\n";
    value = 1345;
    vec_res = linearSearch(vec.begin(), vec.end(), value);
    if (vec_res == vec.end())
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << *vec_res << std::endl;

    std::cout << std::endl;

    // Usage with deque
    std::deque<int> deq{ -56421,-32554, -6547, -254, 12, 65, 987, 987, 1026, 1235, 56462, 5674985 };

    std::cout << "EXAMPLE WITH DEQUE(EXISTING VALUE)\n";
    value = 1235;
    DEQUE_ITERATOR deq_res = linearSearch(deq.begin(), deq.end(), value);
    if (deq_res == deq.end())
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << *deq_res << std::endl;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH DEQUE(NOT EXISTING VALUE)\n";
    value = 1345;
    deq_res = linearSearch(deq.begin(), deq.end(), value);
    if (deq_res == deq.end())
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << *deq_res;

    std::cout << std::endl;

    // Usage with array
    std::array<int, 12> arr{ -56421,-32554, -6547, -254, 12, 65, 987, 987, 1026, 1235, 56462, 5674985 };

    std::cout << "EXAMPLE WITH ARRAY(EXISTING VALUE)\n";
    value = 1235;
    ARRAY_ITERATOR arr_res = linearSearch(arr.begin(), arr.end(), value);
    if (arr_res == arr.end())
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << *arr_res << std::endl;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH ARRAY(NOT EXISTING VALUE)\n";
    value = 1345;
    arr_res = linearSearch(arr.begin(), arr.end(), value);
    if (arr_res == arr.end())
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << *arr_res;

    std::cout << std::endl;

    // Usage with Bidirectional list
    std::list<int> lst{ -56421,-32554, -6547, -254, 12, 65, 987, 987, 1026, 1235, 56462, 5674985 };

    std::cout << "EXAMPLE WITH BIDIRECTIONAL LIST(EXISTING VALUE)\n";
    value = 1235;
    LIST_ITERATOR lst_res = linearSearch(lst.begin(), lst.end(), value);
    if (lst_res == lst.end())
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << *lst_res << std::endl;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH BIDIRECTIONAL LIST(NOT EXISTING VALUE)\n";
    value = 1345;
    lst_res = linearSearch(lst.begin(), lst.end(), value);
    if (lst_res == lst.end())
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << *lst_res << std::endl;

    std::cout << std::endl;
}

template <typename Container>
int linearSearch(const Container& container, std::size_t begin, std::size_t end, typename Container::value_type value)
{

    std::size_t end_not_found = end;

    if (container[begin] == value)
        return begin;
    if (container[end] == value)
        return end;

    while (begin < end)
    {
        if (container[begin] == value)
            return begin;
        ++begin;
    }

    return -1;

}

void example_with_index()
{
    // Usage with vector
    std::vector<int> vec{ -56421,-32554, -6547, -254, 12, 65, 987, 987, 1026, 1235, 56462, 5674985 };

    std::cout << "EXAMPLE WITH VECTOR(EXISTING VALUE)\n";
    int value = 1235;
    int vec_res = linearSearch(vec, 0, vec.size() - 1, value);
    if (vec_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << vec[vec_res] << std::endl;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH VECTOR(NOT EXISTING VALUE)\n";
    value = 1345;
    vec_res = linearSearch(vec, 0, vec.size() - 1, value);
    if (vec_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << vec[vec_res] << std::endl;

    std::cout << std::endl;

    // Usage with deque
    std::deque<int> deq{ -56421,-32554, -6547, -254, 12, 65, 987, 987, 1026, 1235, 56462, 5674985 };

    std::cout << "EXAMPLE WITH DEQUE(EXISTING VALUE)\n";
    value = 1235;
    std::size_t deq_res = linearSearch(deq, 0, deq.size() - 1, value);
    if (deq_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << deq[deq_res] << std::endl;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH DEQUE(NOT EXISTING VALUE)\n";
    value = 1345;
    deq_res = linearSearch(deq, 0, deq.size() - 1, value);
    if (deq_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << deq[deq_res] << std::endl;

    std::cout << std::endl;

    // Usage with array
    std::array<int, 12> arr{ -56421,-32554, -6547, -254, 12, 65, 987, 987, 1026, 1235, 56462, 5674985 };

    std::cout << "EXAMPLE WITH ARRAY(EXISTING VALUE)\n";
    value = 1235;
    int arr_res = linearSearch(arr, 0, arr.size() - 1, value);
    if (arr_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << arr[arr_res] << std::endl;

    std::cout << std::endl;

    std::cout << "EXAMPLE WITH ARRAY(NOT EXISTING VALUE)\n";
    value = 1345;
    arr_res = linearSearch(arr, 0, arr.size() - 1, value);
    if (arr_res == -1)
        std::cout << "Value " << value << " not found\n";
    else
        std::cout << "Here is your found value: " << arr[arr_res] << std::endl;
}

int main()
{
    std::cout << " --------------------------------ITERATOR_USE---------------------------------\n";
    example_with_iterator();
    std::cout << " --------------------------------ITERATOR_USE---------------------------------\n\n";

    std::cout << " --------------------------------INDEX_USE------------------------------------\n";
    example_with_index();
    std::cout << " --------------------------------INDEX_USE------------------------------------\n";
}