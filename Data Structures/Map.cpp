/// ------------------------------------------------------MAP-----------------------------------------------------------------------------
#include <utility>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstddef>
#include <map>

template <class Key, class Value> 
class Map {
private:
    using key_type = Key;
    using mapped_type = Value;
    using ValueType = std::pair<const Key, const Value>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = ValueType&;
    using const_reference = const ValueType&;

    struct Node {
        Node* left{ nullptr };
        Node* parent{ nullptr };
        Node* right{ nullptr };
        std::pair<Key, Value> data{};

        Node(Node* left, Node* parent, Node* right, ValueType data)
            : left{ left }, parent{ parent }, right{ right }, data{ data } {}
    };
    Node* root{ nullptr };

    

public:
    class Iterator;
    class ConstIterator;

    // Creating empty map
    Map() : root{ nullptr } {};

    // Creating new map, which is the deep copy of other [O(n)]
    //  Map<std::string, int> map;
    //  map["something"] = 69;
    //  map["anything"] = 199;
    //  Map<std::string, int> copied{map};
    //  copied["something"] == map["something"] == 69
    Map(const Map& other) { CopyTree(&root, other.root); }

    // Move constructor
    Map(Map&& other) { std::swap(root, other.root); }

    Map& operator=(const Map& other) {
        Map tmp{ other };
        std::swap(root, tmp.root);
        return *this;
    }

    Map& operator=(Map&& other) {
        Map tmp{ std::move(other) };
        std::swap(root, tmp.root);
        return *this;
    }

    // Cleaning the memory 
    ~Map() { clear(); }

    // Returns iterator on the first element
    Iterator begin() {
        if (root == nullptr) {
            return Iterator{ nullptr };
        }
        auto current = root;
        while (current && current->left) {
            current = current->left;
        }
        return Iterator{ current };
    }

    // Returns const iterator on the first element
    ConstIterator begin() const {
        if (root == nullptr) {
            return ConstIterator{ nullptr };
        }
        auto current = root;
        while (current && current->left) {
            current = current->left;
        }
        return ConstIterator{ current };
    }

    // Return iterator on the next element of end of the container
    Iterator end() { return Iterator{ nullptr }; }

    // Return const iterator on the next element of end of the container
    ConstIterator end() const { return ConstIterator{ nullptr }; }

    // Returns the size of map (how many nodes)
    std::size_t size() const { return std::distance(begin(), end()); }

    void CopyTree(Node** current, Node* other) {
        // if (other->right) {
        //   current->right = new Node{nullptr, current, nullptr, other->data}; 
        //   CopyTree(current->right, other->right);
        // }
        // if (other->left) {
        //   current->left = new Node{nullptr, current, nullptr, other->data};
        //   CopyTree(current->left, other->left);
        // } 

        if (other) { *current = new Node{ nullptr, nullptr, nullptr, other->data }; }
        if (other->right) {
            // current->right = new Node{nullptr, current, nulltr, other->right->data}; 
            CopyTree(&((*current)->right), other->right);
        }
        if (other->left) { CopyTree(&((*current)->left), other->left); }
    }
    Iterator find(const Key& key) {
        auto current = root;
        while (current) {
            if (key == current->data.first) {
                return Iterator{ current };
            }
            else if (key > current->data.first) {
                current = current->right;
            }
            else if (key < current->data.first) {
                current = current->left;
            }
            else {
                break;
            }
        }
        return end();
    }

    ConstIterator find(const Key& key) const {
        auto current = root;
        while (current) {
            if (key == current->data.first) {
                return ConstIterator{ current };
            }
            if (key > current->data.first) {
                current = current->right;
            }
            if (key < current->data.first) {
                current = current->left;
            }
            else {
                break;
            }
        }
        return end();
    }

    // Check, if there is an element with such key in container
    bool contains(const Key& key) const { return find(key) != end(); }

    // Returns element by key. If there is no element with such key, throws exception
    // std::out_if_range
    const Value& operator[](const Key& key) const {
        if (find(key) != end()) {
            return (*find(key)).second;
        }
        throw std::out_of_range("no such key");
    }

    // Returns a reference to an element by key (allows you to change the element). If in
    // there is no element in the dictionary with such a key that creates it and sets it
    // default value, after which a link is returned using it.map["something"]
    // = 75;
    Value& operator[](const Key& key) {
        if (find(key) == end()) {
            //   std::cout<<"push"<<std::endl;
            push(key, {});
        }
        // std::cout<<root<<std::endl;
        return (*find(key)).second;
    }

    // Deleting element by key and return value of deleted element
    // Map<int, std::string> c =
    //   {
    //       {1, "one" }, {2, "two" }, {3, "three"},
    //       {4, "four"}, {5, "five"}, {6, "six"  }
    //   };
    // c.erase(4) == true
    // c =
    //   {
    //       {1, "one" }, {2, "two" }, {3, "three"},
    //             {5, "five"}, {6,"six"  }
    //   }; result after erase
    bool erase(const Key& key) {
        if (!root) {
            return false;
        }
        Node* current = root;
        while (current) {
            if (key == current->data.first) {
                // no child nodes
                if (!current->left && !current->right) {
                    delete current;
                    root = nullptr;
                    break;
                }
                // has 1 left node
                if (current->left && !current->right) {
                    // has parent
                    if (current->parent) {
                        if (current->data.first < current->parent->data.first) {
                            current->parent->left = current->left;
                            current->right->parent = current->parent;
                            delete current;
                            break;
                        }
                        else {
                            current->parent->right = current->left;
                            current->left->parent = current->parent;
                            delete current;
                            break;
                        } // doesn't have parent
                    }
                    else {
                        root = current->left;
                        return true;
                    }
                }// the same for right
                if (current->right && !current->left) {
                    if (current->parent) {
                        if (current->data.first > current->parent->data.first) {
                            current->parent->right = current->right;
                            current->right->parent = current->parent;
                            delete current;
                            break;
                        }
                        else {
                            current->parent->left = current->right;
                            current->right->parent = current->parent;
                            delete current;
                            break;
                        } // doesn't have parent
                    }
                    else {
                        root = current->right;
                        return true;
                    }
                }// ends here

             // the case where its needed to find successor
                if (current->left && current->right) {
                    Node* successor = current;
                    successor = successor->right;
                    while (successor->left) {
                        successor = successor->left;
                    }

                    std::swap(current->data, successor->data);
                    if (successor->right) {
                        successor->parent->left = successor->right;
                        successor->right->parent = successor->parent;
                    }
                }

                delete current;
                return true;
            }
            else if (key > current->data.first) { // x on the right side
                current = root->right;
            }
            else { // x on the left side
                current = root->left;
            }
        }
        return false;
    }

    void insert(const Key& key, const Value& value) {
        if (!root) {
            root = new Node{ nullptr, nullptr, nullptr, {key, value} };
            return;
        }

        Node* current = root;
        while (current) {
            if (key == current->data.first) {
                // Element with the same key already exists, do nothing.
                return;
            }
            else if (key < current->data.first) {
                if (!current->left) {
                    current->left = new Node{ nullptr, current, nullptr, {key, value} };
                    break;
                }
                else {
                    current = current->left;
                }
            }
            else {
                if (!current->right) {
                    current->right = new Node{ nullptr, current, nullptr, {key, value} };
                    break;
                }
                else {
                    current = current->right;
                }
            }
        }
    }

    // Swapping container with other
    void swap(Map& other) { std::swap(root, other.root); }

    // Returns iterator on the frist element, which is not smaller then given key [O(h)]
    Iterator lower_bound(const Key& key) {
        if (!root) {
            return end();
        }
        auto current = root;

        while (current) {
            if (current->right && key > current->data.first) {
                current = root->right;
            }
            else if (current->left && key < current->data.first) {
                current = root->left;
            }
            else {
                break;
            }
        }
        return current;
    }

    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

    // Clearing container [O(n)]
    // Map<int, std::string> c =
    //   {
    //       {1, "one" }, {2, "two" }, {3, "three"},
    //       {4, "four"}, {5, "five"}, {6, "six"  }
    //   };
    // c.clear;
    // c.size() == 0 //true;
    void clear() {
        clear(root);
        root = nullptr;
    }

    class Iterator {
    private:
        Node* node;

    public:
        // ���������:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = Key;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(Node* node) : node{ node } {}
        // ���������. �������� � ���������� ��������.
        Iterator& operator++() {

            // one to the right child then down to the left bottom
            if (node->right) {
                node = node->right;
                while (node && node->left) {
                    node = node->left;
                }
            }
            // up to parent which was not iterated
            else {
                while (node->parent && node->data.first > node->parent->data.first) {
                    node = node->parent;
                }
                node = node->parent;
            }
            return *this;
        }

        // ���������. �������� � ����������� ��������.
        Iterator& operator--() {
            // one to the left parent then to the right
            if (node->left) {
                node = node->left;
                while (node && node->right) {
                    node = node->right;
                }
            }
            else {
                while (node->data.first < node->parent.data.first) {
                    node = node->parent;
                }
                node = node->parent;
            }
            return *this;
        }

        bool operator==(const Iterator& other) { return node == other.node; }
        // �������� �� ����������� ���� ����������.
        bool operator!=(const Iterator& other) { return node != other.node; }

        // ������������� (��� � �����������): *it = 42; ��� std::cout << *it;
        std::pair<Key, Value>& operator*() { return node->data; }
        const std::pair<Key, Value>* operator->() { return &(node->data); }
    };
    class ConstIterator {
    private:
        Node* node;

    public:
        // ���������
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = Key;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        ConstIterator(Node* node) : node{ node } {}

        ConstIterator& operator++() {

            // one to the right child then down to the left bottom
            if (node->right) {
                node = node->right;
                while (node && node->left) {
                    node = node->left;
                }
            }
            // up to parent which was not iterated
            else {
                while (node->parent && node->data.first > node->parent->data.first) {
                    node = node->parent;
                }
                node = node->parent;
            }
            return *this;
        }
        ConstIterator& operator--() {
            // one to the left parent then to the right
            if (node->left) {
                node = node->left;
                while (node && node->right) {
                    node = node->right;
                }
            }
            else {
                while (node->data.first < node->parent.data.first) {
                    node = node->parent;
                }
                node = node->parent;
            }
            return *this;
        }

        bool operator!=(const ConstIterator& other) { return node != other.node; }

        bool operator==(const ConstIterator& other) { return node == other.node; }

        // ������������ ������� �� Iterator, ��� ���������� ����������� ������
        const std::pair<Key, Value>& operator*() { return node->data; }

        const std::pair<Key, Value>* operator->() { return &(node->data); }
    };
};

int main()
{
    
    
}