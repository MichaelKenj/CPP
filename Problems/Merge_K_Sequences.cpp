/// Merge K sequences-------------------------------------------------------------
#include <iostream>
#include <list>
#include <queue>


typedef std::list< int > list_type;
// Type of input & output sequences.                                             |

typedef std::pair< int, int > item_type;
// Such item denotes the actual value, and index of the                          |
// container, from which taht value was taken.                                   |
//                                                                               |
//                                                                               |
/// Merges provided K lists into a single one, using prioerity queue.            |   
list_type k_merge(list_type* containers[], int k)
{
    std::priority_queue< item_type > pq;
    // Insert heads of all lists into the priority queue.
    for (int i = 0; i < k; ++i) {
        pq.push(item_type(containers[i]->front(), i));
        containers[i]->pop_front();
    }
    // Prepare result list
    list_type result;
    // Extract maximal values, and replace them with their successors
    while (!pq.empty()) {
        result.push_back(pq.top().first);  // Place the maximal value  
        // into result sequence
        int index = pq.top().second;  // Remember the container
        pq.pop();  // Remove the maximal value from priority queue
        if (!containers[index]->empty()) {
            pq.push(item_type(containers[index]->front(), index));
            // Place the next value of that container into the queue
            containers[index]->pop_front();  // And remove it from the container
        }
    }
    return result;
}


/// Prints all values in [begin, end) to the screen.                             |
template< typename InIt >
void print_sequence(InIt begin, InIt end)
{
    std::cout << " [";
    for (; begin != end; ++begin)
        std::cout << " " << *begin;
    std::cout << " ]" << std::endl;
}

void usage_merge_k_seq()
{
    std::cout << " - Merging K sequences - " << std::endl;

    std::list< int > l1 = { 12, 8, 7, 4, 2 };
    std::list< int > l2 = { 20, 19, 9, 6, 3 };
    std::list< int > l3 = { 18, 17, 10, 5, 1 };
    std::cout << "Input sequences: " << std::endl;
    print_sequence(l1.cbegin(), l1.cend());
    print_sequence(l2.cbegin(), l2.cend());
    print_sequence(l3.cbegin(), l3.cend());

    std::list< int >* containers[] = { &l1, &l2, &l3 };
    std::list< int > result = k_merge(containers, 3);
    std::cout << "Output sequence: " << std::endl;
    print_sequence(result.cbegin(), result.cend());
}

int main()
{
    usage_merge_k_seq();
}