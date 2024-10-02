e <iostream>


template <typename T>
struct Node
{
	T _value;
	Node* _left;
	Node* _right;
	Node(T value = T{}, Node* left = nullptr, Node* right = nullptr) : _value(value), _left(left), _right(right)
	{}

	~Node() = default;

};

/// <summary>
/// Searches for a node with the given value. Returns the node if found; otherwise, returns nullptr.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="root"></param>
/// <param name="value"></param>
/// <returns></returns>
template <typename T>
Node<T>* binarySearch(Node<T>* root, T value)
{
    Node<T>* ptr = root;
    if (root->_value == value)
        return root;
    while (ptr != nullptr)
    {
        if (ptr->_value < value)
            ptr = ptr->_right;
        else if (ptr->_value > value)
            ptr = ptr->_left;
        else
            return ptr;
    }

    return nullptr;
}


int main()
{
    Node<int>* A = new Node<int>(5);
    Node<int>* B = new Node<int>(3);
    Node<int>* C = new Node<int>(7);
    Node<int>* D = new Node<int>(2);
    Node<int>* E = new Node<int>(4);
    Node<int>* F = new Node<int>(6);
    Node<int>* G = new Node<int>(8);

    // Link nodes to form a BST
    A->_left = B;
    A->_right = C;
    B->_left = D;
    B->_right = E;
    C->_left = F;
    C->_right = G;

    //      A               5                
    //   /     \         /     \       
    //  B       C       3       7
    // / \     / \     / \     / \
    //D   E   F   G   2   4   6   8


    int value = 5;
    Node<int>* searchable_node = binarySearch(A, value);
    if (searchable_node == nullptr)
        std::cout << "Node with value " << value << " not found\n";
    else
        std::cout << "Node with value " << value << " found!!!\n";


}
