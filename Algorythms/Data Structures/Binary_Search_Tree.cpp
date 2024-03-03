/// -----------------------------------------------BINARY SEARCH TREE---------------------------------------------------------------------
// -----------!!!IMPORTANT!!!------------
// This tree class is not self balanced

#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <queue>


/// MICHAELKENJ's IMPLEMENTED BINARY_SEARCH_TREE CLASS
/// without access to node, only member functions

template <typename T>
class BinarySearchTree {
private:

    /// Node
    template <typename T>
    struct Node {
        T data;
        Node<T>* parent;
        Node<T>* left;
        Node<T>* right;

        Node(T value, Node<T>* parentPtr = nullptr) : data(value), left(nullptr), right(nullptr), parent(parentPtr) {}
        void print()
        {
            std::cout << data << " ";
        }
    };

     
    /// Private member
    Node<T>* root = nullptr;


    // For insert, recursive
    Node<T>* insert(Node<T>* root, T value, Node<T>* parent = nullptr) {
        if (root == nullptr) {
            return new Node<T>(value, parent);
        }

        if (value < root->data) {
            root->left = insert(root->left, value, root);
        }
        else if (value > root->data) {
            root->right = insert(root->right, value, root);
        }

        return root;
    }

    // For remove, recursive
    Node<T>* remove(Node<T>* root, T value) {
        if (root == nullptr) {
            return nullptr;
        }

        if (value < root->data) {
            root->left = remove(root->left, value);
        }
        else if (value > root->data) {
            root->right = remove(root->right, value);
        }
        else {
            if (root->left == nullptr) {
                Node<T>* temp = root->right;
                if (temp) {
                    temp->parent = root->parent;
                }
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node<T>* temp = root->left;
                if (temp) {
                    temp->parent = root->parent;
                }
                delete root;
                return temp;
            }

            Node<T>* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }

        return root;
    }

    // Used in remove
    Node<T>* minValueNode(Node<T>* node) {
        Node<T>* current = node;

        while (current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

    // For destructor, recursive
    void destroyTree(Node<T>* root) {
        if (root != nullptr) {
            destroyTree(root->left);
            destroyTree(root->right);
            delete root;
        }
    }

    // For tree size
    std::size_t calculateHeight(Node<T>* node) const {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);

        return 1 + std::max(leftHeight, rightHeight);
    }


    // InOrder, recursive
    void inOrderTraversal(Node<T>* root) {
        if (root != nullptr) {
            inOrderTraversal(root->left);
            std::cout << root->data << " ";
            inOrderTraversal(root->right);
        }
    }

    // PreOrder, recursive
    void preOrderTraversal(Node<T>* root) {
        if (root != nullptr) {
            std::cout << root->data << " ";
            preOrderTraversal(root->left);
            preOrderTraversal(root->right);
        }
    }

    //PostOrder, recursive
    void postOrderTraversal(Node<T>* root) {
        if (root != nullptr) {
            postOrderTraversal(root->left);
            postOrderTraversal(root->right);
            std::cout << root->data << " ";
        }
    }

public:

    // Iterator
    class iterator {
    public:
        using value_type = T;
        using pointer = value_type*;
        using reference = const value_type&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        using node_type = Node<value_type>;

        explicit iterator(node_type* head = nullptr) : mPtr(head) {
            if (mPtr != nullptr) {
                while (mPtr->left) {
                    moveToLeft();
                }
            }
        }

        reference operator*() const {
            return mPtr->data;
        }

        pointer operator->() {
            return &(mPtr->data);
        }

        // Works with InOrder principle
        iterator& operator++() {
            if (mPtr->right != nullptr) {
                moveToRight();
                while (mPtr->left != nullptr) {
                    moveToLeft();
                }
            }
            else if (!stack.empty()) {
                mPtr = stack.top();
                stack.pop();
            }
            else {
                mPtr = nullptr;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }



        bool operator==(const iterator& b) const {
            return this->mPtr == b.mPtr;
        }

        bool operator!=(const iterator& b) const {
            return this->mPtr != b.mPtr;
        }

    private:
        void moveToLeft() {
            stack.push(mPtr);
            mPtr = mPtr->left;
        }

        void moveToRight() {
            mPtr = mPtr->right;
        }
        std::stack<node_type*> stack;
        node_type* mPtr;
    };

    // Const Iterator
    class const_iterator {
    public:
        using value_type = T;
        using pointer = const value_type*;
        using reference = const value_type&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        using node_type = Node<value_type>;

        explicit const_iterator(node_type* head = nullptr) : mPtr(head) {
            if (mPtr != nullptr) {
                while (mPtr->left) {
                    moveToLeft();
                }
            }
        }

        reference operator*() const {
            return mPtr->data;
        }

        pointer operator->() const {
            return &(mPtr->data);
        }

        // Works with InOrder principle
        const_iterator& operator++() {
            if (mPtr->right != nullptr) {
                moveToRight();
                while (mPtr->left != nullptr) {
                    moveToLeft();
                }
            }
            else if (!stack.empty()) {
                mPtr = stack.top();
                stack.pop();
            }
            else {
                mPtr = nullptr;
            }
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const const_iterator& b) const {
            return this->mPtr == b.mPtr;
        }

        bool operator!=(const const_iterator& b) const {
            return this->mPtr != b.mPtr;
        }

    private:
        void moveToLeft() {
            stack.push(mPtr);
            mPtr = mPtr->left;
        }

        void moveToRight() {
            mPtr = mPtr->right;
        }

        std::stack<node_type*> stack;
        node_type* mPtr;
    };

    // -----------For Iterators
    iterator begin() {
        return iterator(this->root);
    }

    iterator end() {
        return iterator(nullptr);
    }

    const_iterator cbegin() const {
        return const_iterator(root);
    }

    const_iterator cend() const {
        return const_iterator(nullptr);
    }
    // -------------------------

    BinarySearchTree() : root(nullptr) {}

    // Constructor, with vector, malo li
    BinarySearchTree(const std::vector<T>& vec)
    {
        for (const auto& i : vec)
        {
            insert(i);
        }

    }

    // Constructor, with list, malo li
    BinarySearchTree(const std::list<T>& list)
    {
        for (const auto& i : list)
        {
            insert(i);
        }
    }

    ~BinarySearchTree() {
        destroyTree(root);
    }

    // Insert, recursive
    void insert(T value) {
        root = insert(root, value);
    }

    // Insert, iterative
    /*void insert(T value) {
        Node<T>* newNode = new Node<T>(value);

        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node<T>* current = root;
        Node<T>* parent = nullptr;

        while (current != nullptr) {
            parent = current;

            if (value < current->data) {
                current = current->left;
            }
            else if (value > current->data) {
                current = current->right;
            }
            else {
                // Duplicate values are not allowed in this simple implementation.
                // You can modify this part based on your requirements.
                delete newNode; // Cleanup the allocated memory for duplicate value.
                return;
            }
        }

        if (value < parent->data) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
    }*/

    // Remove, recursive
    void remove(T value) {
        root = remove(root, value);
    }

    // Remove, iterative
    /*
    void remove(T value) {
        Node<T>* current = root;
        Node<T>* parent = nullptr;

        while (current != nullptr && current->data != value) {
            parent = current;

            if (value < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        if (current == nullptr) {
            // Value not found
            return;
        }

        // Node with only one child or no child
        if (current->left == nullptr) {
            Node<T>* temp = current->right;
            if (parent == nullptr) {
                root = temp;
            }
            else if (current == parent->left) {
                parent->left = temp;
            }
            else {
                parent->right = temp;
            }
            delete current;
        }
        else if (current->right == nullptr) {
            Node<T>* temp = current->left;
            if (parent == nullptr) {
                root = temp;
            }
            else if (current == parent->left) {
                parent->left = temp;
            }
            else {
                parent->right = temp;
            }
            delete current;
        }
        else {
            // Node with two children: Get the inorder successor (smallest
            // in the right subtree)
            Node<T>* successor = minValueNode(current->right);

            // Copy the inorder successor's data to this node
            current->data = successor->data;

            // Delete the inorder successor
            parent = current;
            current = current->right;

            while (current->left != nullptr) {
                parent = current;
                current = current->left;
            }

            if (parent->left == current) {
                parent->left = current->right;
            }
            else {
                parent->right = current->right;
            }

            delete current;
        }
    }
    */

    bool search(T value) {
        Node<T>* current = root;

        while (current != nullptr) {
            if (value == current->data) {
                return true;
            }
            else if (value < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        return false;
    }

    // Size of tree
    std::size_t size() const
    {
        return calculateHeight(root);
    }

    // Max depth in tree
    std::size_t maxHeight() const
    {
        //xz
    }

    /// left - root - right
    void inOrderTraversal() {
        inOrderTraversal(root);
        std::cout << std::endl;
    }

    /// root - left - right
    void preOrderTraversal() {
        std::cout << "Pre-order traversal: ";
        preOrderTraversal(root);
        std::cout << std::endl;
    }

    /// left - right - root
    void postOrderTraversal() {
        std::cout << "Post-order traversal: ";
        postOrderTraversal(root);
        std::cout << std::endl;
    }

    /// BFS
    void printBFS() const {
        if (root == nullptr) {
            return;
        }

        std::queue<Node<T>*> bfsQueue;
        bfsQueue.push(root);

        while (!bfsQueue.empty()) {
            Node<T>* current = bfsQueue.front();
            bfsQueue.pop();

            current->print();

            if (current->left != nullptr) {
                bfsQueue.push(current->left);
            }

            if (current->right != nullptr) {
                bfsQueue.push(current->right);
            }
        }

        std::cout << std::endl;
    }
};


int main()
{
    BinarySearchTree<int> bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);
    bst.printBFS();
    //      A               5                
    //   /     \         /     \       
    //  B       C       3       7
    // / \     / \     / \     / \
    //D   E   F   G   2   4   6   8
}