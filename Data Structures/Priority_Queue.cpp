/// -------------------------------------------------PRIORITY_QUEUE-----------------------------------------------------------------------


// Compare is a function or functor that is used for comparison. By
// the default is just std::less - the same as the < operator. That is
// Compare(1, 2) == true and Compare(2, 1) == false.Note: By default with this
// comparator, the queue should work as a max heap
#include <iostream>
#include <algorithm>
#include <vector>

template <class T, class Compare = std::less<T>>
class PriorityQueue {
private:
    std::vector<T> data;
    Compare compare{};
    using container_type = std::vector<T>;
    using value_compare = Compare;
    using value_type = typename std::vector<T>::value_type;
    using size_type = typename std::vector<T>::size_type;
    using reference = typename std::vector<T>::reference;
    using const_reference = typename std::vector<T>::const_reference;

    void balance() {
        std::size_t i = data.size() - 1;
        while (i != 0) {
            std::size_t parent = (i - 1) / 2;
            if (compare(data[i], data[parent]) == 0) {
                std::swap(data[i], data[parent]);
                i = parent;
            }
            else {
                break;
            }
        }
    }

    void heapify() {
        for (std::size_t i = (data.size()) / 2; i != -1; --i) {
            std::size_t current = i;
            int left = 2 * current + 1;
            int right = 2 * current + 2;

            std::size_t biggest;
            while (true) {
                left = 2 * current + 1;
                right = 2 * current + 2;

                if (compare(left, data.size()) && compare(right, data.size())) {
                    if (data[left] > data[right]) {
                        biggest = left;
                    }
                    else {
                        biggest = right;
                    }
                }
                else if (compare(left, data.size()) && !compare(right, data.size())) {
                    biggest = left;
                }
                else {
                    break;
                }

                if (!compare(data[current], data[biggest])) {
                    break;
                }
                std::swap(data[current], data[biggest]);
                current = biggest;
            }
        }
    }

public:
    // Creates an empty priority queue
    PriorityQueue() = default;

    // Creates a new priority queue, deep copying the other queue [O(n)]
    PriorityQueue(const PriorityQueue& other) = default;

    PriorityQueue(const std::vector<T> vec) : data(vec) { heapify(); }

    // Overwrites the current priority queue with the other queue
    PriorityQueue& operator=(const PriorityQueue& other) = default;

    // Creates a new priority queue by moving an existing one [O(1)]
    PriorityQueue(PriorityQueue&& other) = default;

    // Assigns the current priority queue with another one
    PriorityQueue& operator=(PriorityQueue&& other) = default;

    // Clears the memory of the priority queue
    ~PriorityQueue() = default;

    // Gets a reference to the top element of the priority queue
    const_reference top() const { return data.front(); }

    // Checks if the container is empty
    bool empty() const { return data.empty(); }

    // Returns the size of the priority queue (how much memory is already occupied)
    size_type size() const { return data.size(); }

    // Adds an element to the priority queue
    void push(const value_type& value) {
        data.push_back(value);
        balance();
    }

    // Adds an element to the priority queue
    void push(const value_type&& value) {
        data.push_back(std::move(value));
        balance();
    }

    template <class... Args> void emplace(Args &&...value) {
        data.emplace_back(std::forward<Args>(value)...);
        balance();
    }

    // Removes an element from the beginning of the priority queue. Returns the removed element.
    T pop() {
        std::size_t current = 0;
        int left = 2 * current + 1;
        int right = 2 * current + 2;
        std::size_t last = data[0];
        std::size_t biggest;
        std::swap(data[0], data[data.size() - 1]);
        data.pop_back();
        while (true) {
            left = 2 * current + 1;
            right = 2 * current + 2;
            if (compare(left, data.size()) && compare(right, data.size())) {
                if (data[left] > data[right]) {
                    biggest = left;
                }
                else {
                    biggest = right;
                }
            }
            else if (compare(left, data.size()) && !compare(right, data.size())) {
                biggest = left;
            }
            else {
                break;
            }

            if (!compare(data[current], data[biggest])) {
                break;
            }
            std::swap(data[current], data[biggest]);
            current = biggest;
        }
        return last;
    }

    // Swaps the content with another priority queue. q1.swap(q2);
    void swap(PriorityQueue& other) { std::swap(data, other.data); }
};

int main()
{
    // Example usage goes here
}
