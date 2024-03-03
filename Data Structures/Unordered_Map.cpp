/// -------------------------------------------------UNORDERED_MAP-----------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

template <class Key, class Value> class UnorderedMap {
private:
    using ValueType = std::pair<Key, Value>;
    std::vector<std::list<ValueType>> data{};
    std::size_t s = 0;

    void set(const Key& key, Value& value) {
        std::size_t hashed = std::hash<Key>{}(key);
        data[hashed % data.size()].push_front({ key, value });
        ++s;
    }

public:
    class Iterator;
    class ConstIterator;
    // Creates an empty dictionary
    UnorderedMap() : data{ 8 } {}

    // Creates a new UnorderedMap, deep copying 'other' [O(n)]
    // UnorderedMap<std::string, int> map;
    // map["something"] = 69;
    // map["anything"] = 199;
    // UnorderedMap<std::string, int> copied{map};
    // copied["something"] == map["something"] == 69
    UnorderedMap(const UnorderedMap& other) = default;

    // Move constructor
    UnorderedMap(UnorderedMap&& other) {
        std::swap(data, other.data);
        std::swap(s, other.s);
    }

    // Overwrites the current dictionary with 'other'
    UnorderedMap& operator=(const UnorderedMap& other) {
        UnorderedMap tmp{ other };
        std::swap(data, tmp.data);
        std::swap(s, tmp.s);
        return *this;
    }

    // Move assignment
    UnorderedMap& operator=(UnorderedMap&& other) {
        UnorderedMap tmp{ std::move(other) };
        std::swap(data, tmp.data);
        std::swap(s, tmp.s);
        return *this;
    }

    ~UnorderedMap() = default;

    // Returns an iterator to the first element
    Iterator begin() { return Iterator{ data.begin(), --data.end() }; }

    // Returns a constant iterator to the first element
    ConstIterator begin() const {
        return ConstIterator{ Iterator{data.begin(), --data.end()} };
    }

    // Returns an iterator denoting the end of the container (after the last element)
    Iterator end() { return Iterator{ data.end() - 1 }; }

    // Returns a constant iterator denoting the end of the container
    ConstIterator end() const { return ConstIterator{ Iterator{data.end() - 1} }; }

    // Returns the size of UnorderedMap (how many elements are added)
    std::size_t size() const {
        return s;
    }

    // Checks if UnorderedMap is empty
    bool empty() const { return !s; }

    // Returns the element by key. If absent, throws an exception
    const Value& operator[](Key key) const {
        size_t hashed = std::hash<Key>{}(key);
        for (const auto& pair : data[hashed % data.size()]) {
            if (key == pair.first) {
                return pair.second;
            }
        }
        throw std::out_of_range{ "No such a key here" };
    }

    // Returns a reference to the element by Key (allows modification of the element). If
    // the element with the same key is absent, creates and initializes it with the default
    // value map["something"] = 75;
    Value& operator[](Key key) {
        size_t hashed = std::hash<Key>{}(key);
        for (auto& pair : data[hashed % data.size()]) {
            if (key == pair.first) {
                return pair.second;
            }
        }
        insert(key, Value{});
        return (*find(key)).second;
    }

    // Checks if there is an element with the given Key in the container
    bool contains(const Key& key) const {
        size_t idx = std::hash<Key>{}(key);
        for (const auto& it : data[idx % data.size()]) {
            if (it.first == key) {
                return true;
            }
        }
        return false;
    }

    // Returns an Iterator to the element being searched for; if no such element
    // returns an iterator to the last element
    Iterator find(const Key& key) {
        size_t idx = std::hash<Key>{}(key);
        for (auto it = data[idx % data.size()].begin(); it != data[idx % data.size()].end(); ++it) {
            if (it->first == key) {
                return Iterator(it);
            }
        }
        return end();
    }

    // Adds a new element with the given key and value if there is no existing
    // element with the same key. Map<int, std::string> c =//   {
    //       {1, "one" }, {2, "two" }, {3, "three"},
    //       {4, "four"}, {5, "five"}, {6, "six"  }
    //   };
    // c.insert(5, "something");
    // returns false because the element with key = 5 already exists
    bool insert(const Key& k, const Value& v) {
        if (!contains(k)) {
            std::size_t hashed = std::hash<Key>{}(k);
            data[hashed % data.size()].push_back({ k, v });
            ++s;
            return true;
        }
        return false;
    }

    // Removes the element by key and returns the operation result
    // UnorderedMap<int, std::string> c =
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
        size_t idx = std::hash<Key>{}(key);
        auto& collisions = data[idx % data.size()];
        for (auto it = collisions.begin(); it != collisions.end(); ++it) {
            if (key == it->first) {
                collisions.erase(it);
                --s;
                return true;
            }
        }
        return false;
    }

    class Iterator {
    private:
        typename std::vector<std::list<std::pair<Key, Value>>>::iterator it{};
        typename std::vector<std::list<std::pair<Key, Value>>>::iterator list_it_start{};
        typename std::vector<std::list<std::pair<Key, Value>>>::iterator list_it_end{};
        typename std::list<std::pair<Key, Value>>::iterator index{};

    public:
        // Fill
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(typename std::vector<std::list<std::pair<Key, Value>>>::iterator list_it_start,
            typename std::vector<std::list<std::pair<Key, Value>>>::iterator list_it_end)
            : it{ list_it_start }, list_it_start{ list_it_start },
            list_it_end{ list_it_end }, index{ (*list_it_start).begin() } {
            while (index == (*it).end()) {
                if (it == list_it_end) {
                    return;
                }
                ++it;
                index = it.begin();
            }
        }

        Iterator(typename std::vector<std::list<std::pair<Key, Value>>>::iterator list_it_end)
            : it{ list_it_end }, list_it_start{ list_it_end }, list_it_end{ list_it_end },
            index((*list_it_end).end()) {}

        Iterator(typename std::list<std::pair<Key, Value>>::iterator it) : index{ it } {}

        Iterator& operator++() {
            ++index;
            while (index == (*it).end()) {
                if (it != list_it_end) {
                    ++it;
                    index = it.begin();
                }
            }
            return *this;
        }

        bool operator!=(const Iterator& other) { return index != other.index; }
        bool operator==(const Iterator& other) { return index == other.index; }

        // Dereferences the pointer: std::cout << it->second;
        std::pair<Key, Value>& operator->() { return &(*index); }

        // Returns the value of the iterator: *it = {"travel", 42};
        std::pair<Key, Value>& operator*() { return *index; }
    };
    class ConstIterator {
    private:
        Iterator it;

    public:
        // Fill
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        ConstIterator(Iterator it) : it{ it } {}

        ConstIterator& operator++() {
            ++it;
            return *this;
        }

        bool operator!=(const ConstIterator& other) { return it != other.it; }
        bool operator==(const ConstIterator& other) { return it == other.it; }

        // The only difference from Iterator is that it returns a constant reference
        const std::pair<Key, Value>& operator*() { return *it; }
    };
};

int main()
{

}
