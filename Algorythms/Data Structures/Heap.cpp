/// ------------------------------------------------------HEAP----------------------------------------------------------------------------
#include <iostream>
#include <vector>


/// MaxHeap, implemented by HAYRAPETYAN
template< typename ValueType,
    typename ContainerType = std::vector< ValueType > >
class Heap
{
public:
    typedef ValueType value_type;
    typedef ContainerType container_type;
    typedef Heap< ValueType, ContainerType > this_type;

private:
    /// This container stores all elements of the heap, as in 
    /// levels-order traversal.
    container_type data;

public:
    /// Navigation over the tree.
    static int leftChildIndex(int index)
    {
        return index * 2 + 1;
    }
    //
    static int rightChildIndex(int index)
    {
        return index * 2 + 2;
    }
    //
    static int parentIndex(int index)
    {
        return (index - 1) / 2;
    }

public:
    /// Default constructor.
    /// Creates an empty heap.
    Heap()
    {}

    /// Constructor
    /// Creates heap with specified sequence of values.
    template< typename InIt >
    Heap(InIt begin, InIt end)
        : data(begin, end)
    {}

    /// Returns count of values in this heap.
    int n() const
    {
        return (int)data.size();
    }

    /// Checks if subtree of this heap, starting from 'startIndex'
    /// is a valid max-order heap.
    bool isValid(int index = 0) {
        const int leftIndex = leftChildIndex(index),
            rightIndex = rightChildIndex(index);
        if (leftIndex < n()) {
            if (data[leftIndex] > data[index])
                return false;  // Link to "left" is violated
            if (!isValid(leftIndex))
                return false;  // Left subtree is violated
        }
        if (rightIndex < n()) {
            if (data[rightIndex] > data[index])
                return false;  // Link to "right" is violated
            if (!isValid(rightIndex))
                return false;  // Right subtree is violated
        }
        return true;  // All checks have been passed
    }

    /// Checks if given heap contains value 'val'.
    bool contains(const value_type& val) const {
        for (const auto& i : data)
        {
            if (i == val)
                return true;
        }
        return false;
    }

    /// Sifts up the value, currently residing at 'index'.
    void siftUp(int index) {
        int parIndex;
        while (index > 0
            && data[(parIndex = parentIndex(index))] < data[index]) {
            std::swap(data[parIndex], data[index]);
            index = parIndex;
        }
    }

    /// Sifts down the value, currently residing at 'index'.
    void siftDown(int index) {
        while (true) {
            const int leftIndex = leftChildIndex(index),
                rightIndex = rightChildIndex(index);
            // Find the next index downwards
            int nextIndex;
            if (leftIndex >= n())  // This is leaf
                return;
            else if (rightIndex == n())  // Only 1 child
                nextIndex = leftIndex;
            else  // 2 child nodes
                nextIndex = data[leftIndex] > data[rightIndex]
                ? leftIndex
                : rightIndex;
            // Swap with it and proceed
            if (data[index] < data[nextIndex]) {
                std::swap(data[index], data[nextIndex]);
                index = nextIndex;
            }
            else
                return;
        }
    }

    /// Inserts new value 'val' in the heap.
    void push(const value_type& val) {
        data.push_back(val);
        siftUp(n() - 1);
    }

    /// Returns maximal value in the heap.
    const value_type& top() const {
        return data[0];
    }

    /// Removes maximal value from the heap.
    void pop() {
        std::swap(data.front(), data.back());
        data.pop_back();
        siftDown(0);
    }

    /// Considering that values in this heap are in random order,
    /// rearranges them by Floyd's method, in order to do batch 
    /// construction of the heap.
    void constructByFloydMethod() {
        for (int i = n() / 2 - 1; i >= 0; --i)
            siftDown(i);
    }

};

void usage_Is_Valid()
{
    std::cout << " - Checking heaps validity - " << std::endl;

    //            28
    //      14         20
    //   8      6   17    13
    //  4 3   5
    //
    std::vector< int > values_1 = { 28, 14, 20, 8, 6, 17, 13, 4, 3, 5 };
    Heap< int > h1(values_1.cbegin(), values_1.cend());
    std::cout << std::boolalpha <<  "Heap 1 is valid: " << h1.isValid() << std::endl;

    //            28
    //      14         20
    //   8      15   17    13
    //  4 3   7
    //
    std::vector< int > values_2 = { 28, 14, 20, 8, 15, 17, 13, 4, 3, 7 };
    Heap< int > h2(values_2.cbegin(), values_2.cend());
    std::cout << "Heap 2 is valid: " << h2.isValid() << std::endl;
}
void usage_sift_up()
{
    std::cout << " - Sifting up values - " << std::endl;

    //           14
    //      6         17
    //   8     28   20    13
    //  4 3   5
    //
    std::vector< int > values_1 = { 14, 6, 17, 8, 28, 20, 13, 4, 3, 5 };
    Heap< int > h1(values_1.cbegin(), values_1.cend());
    std::cout << "Is heap valid: " << h1.isValid() << std::endl;
    //
    std::cout << "Sifting up index 4 ..." << std::endl;
    h1.siftUp(4);
    std::cout << "Is heap valid: " << h1.isValid() << std::endl;
    //
    std::cout << "Sifting up index 5 ..." << std::endl;
    h1.siftUp(5);
    std::cout << "Is heap valid: " << h1.isValid() << std::endl;
}
void usage_sift_down()
{
    std::cout << " - Sifting down values - " << std::endl;
    //            17
    //      14         28
    //   8      5   20    13
    //  4 3   6
    //
    std::vector< int > values_1 = { 17, 14, 28, 8, 5, 20, 13, 4, 3, 6 };
    Heap< int > h1(values_1.cbegin(), values_1.cend());
    std::cout << "Heap is valid: " << h1.isValid() << std::endl;
    //
    std::cout << "Sifting down index 0 ..." << std::endl;
    h1.siftDown(0);
    std::cout << "Is heap valid: " << h1.isValid() << std::endl;
    //
    std::cout << "Sifting down index 4 ..." << std::endl;
    h1.siftDown(4);
    std::cout << "Is heap valid: " << h1.isValid() << std::endl;
}
void usage_recover_by_Floyd_method()
{
    std::cout << " - Batch construction (Floyd's method) - " << std::endl;

    std::vector< int > values_1 = { 6, 3, 1, 10, 13, 28, 39, 23, 24 };
    Heap< int > h1(values_1.cbegin(), values_1.cend());
    std::cout << "Heap 1 is valid: " << h1.isValid() << std::endl;
    //
    h1.constructByFloydMethod();
    std::cout << "Heap 1 is valid: " << h1.isValid() << std::endl;

    std::vector< int > values_2 = { 9, 8, 18, 17, 14, 23, 26, 34, 19, 6 };
    Heap< int > h2(values_2.cbegin(), values_2.cend());
    std::cout << "Heap 2 is valid: " << h2.isValid() << std::endl;
    //
    h2.constructByFloydMethod();
    std::cout << "Heap 2 is valid: " << h2.isValid() << std::endl;
}

int main()
{
    std::cout << "--------------------------------------\n";
    usage_Is_Valid();
    std::cout << "--------------------------------------\n";
    usage_sift_up();
    std::cout << "--------------------------------------\n";
    usage_sift_down();
    std::cout << "--------------------------------------\n";
    usage_recover_by_Floyd_method();
    std::cout << "--------------------------------------\n";
}