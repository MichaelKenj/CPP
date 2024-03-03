/// ----------------------------------------------------HASH_TABLE--------------------------------------------------------------------------
#include <numeric>
#include <iostream>
#include <list>
#include <vector>
#include <ostream>
#include <iomanip>

/// Closed addressing------------------------------------------------------- 

template< typename InIt >
void print_sequence(InIt begin, InIt end, std::ostream& ostr)
{
    if (begin == end)
        return;
    ostr << *begin;
    while (++begin != end)
        ostr << ", " << *begin;
}


/// This class represents a simple hash table, with chains method used 
/// for collision resolution.
template< typename ValueType, typename HashFuncType >
class HashTable
{
private:
    typedef ValueType value_type;
    typedef HashFuncType hash_function_type;

    typedef std::list< value_type > chain_type;

    typedef std::vector< chain_type > table_type;

    /// Hash function, used to process the values.
    hash_function_type hash_func;

    /// The actual table.
    table_type table;

public:
    /// Constructor
    /// Creates empty hash table with specified size.
    explicit HashTable(
        int m_ = 11,
        const hash_function_type& hash_func_ = hash_function_type())
        : table(m_),
        hash_func(hash_func_)
    {}

    /// Returns size of the table.
    unsigned int m() const
    {
        return (unsigned int)table.size();
    }

    /// Returns number of entries in the table.
    unsigned int size() const
    {
        return std::accumulate(table.cbegin(), table.cend(),
            0u,
            [](unsigned int lft, const chain_type& chain)
            { return lft + (unsigned int)chain.size(); });
    }

    // Access to internal objects
    hash_function_type& hash_f()
    {
        return hash_func;
    }
    const hash_function_type& hash_f() const
    {
        return hash_func;
    }

    /// Prints content of the table to 'ostr'.
    void print(std::ostream& ostr) const {
        for (unsigned int i = 0; i < m(); ++i) {
            ostr << std::setw(4) << i << ": ";
            print_sequence(table[i].cbegin(), table[i].cend(), ostr);
            ostr << std::endl;
        }
        ostr << "----------" << std::endl;
    }

    /// Prints load statistics of the hash table into 'ostr'.
    void print_brief(std::ostream& ostr) const {
        for (unsigned int i = 0; i < m(); ++i)
            ostr << std::setw(4) << ": "
            << std::string(table[i].size(), '*') << std::endl;
        ostr << "----------" << std::endl;
    }

    /// Inserts 'val' into the table.
    void insert(const value_type& val) {
        unsigned int hash_value = hash_func(val);
        unsigned int mapped_cell = hash_value % m();
        table[mapped_cell].push_back(val);
    }

    /// Returns count of entries 'val' in the table.
    unsigned int count(const value_type& val) const {
        unsigned int hash_value = hash_func(val);
        unsigned int mapped_cell = hash_value % m();
        return (unsigned int)std::count(
            table[mapped_cell].cbegin(), table[mapped_cell].cend(),
            val);
    }

    /// Erases all entries of 'val' from the table.
    void erase(const value_type& val) {
        unsigned int hash_value = hash_func(val);
        unsigned int mapped_cell = hash_value % m();
        table[mapped_cell].remove(val);
    }

};

/// A good hash functor for strings.
class StringHash
{
public:
    unsigned int operator()(const std::string& str) const
    {
        unsigned int result = 0;
        unsigned int weight = 1;
        unsigned int weight_diff = 3;
        for (char ch : str) {
            result += ch * weight;
            // Update weight
            weight += weight_diff;
            weight_diff += 2;
        }
        return result;
    }
};

void usage_close_hash()
{
    HashTable< std::string, StringHash > table_1;

    std::cout << " - Inserting values - " << std::endl;
    table_1.insert("abc");
    table_1.insert("xy");
    table_1.insert("Hello");
    table_1.insert("Good");
    table_1.insert("morning");
    table_1.insert("integer");
    table_1.insert("variable");
    table_1.insert("language");
    table_1.insert("string");
    table_1.insert("variant");
    table_1.insert("abcd");

    table_1.print(std::cout);
    std::cout << "Size is " << table_1.size() << std::endl;

    std::cout << " - Querying values - " << std::endl;
    std::cout << "'table' ? " << table_1.count("table") << std::endl;
    std::cout << "'variable' ? " << table_1.count("variable") << std::endl;
    std::cout << "'string' ? " << table_1.count("string") << std::endl;
    std::cout << "'strong' ? " << table_1.count("strong") << std::endl;

    std::cout << " - Erasing values - " << std::endl;
    table_1.erase("xy");
    table_1.erase("Good");
    table_1.erase("integer");

    table_1.print(std::cout);
    std::cout << "Size is " << table_1.size() << std::endl;
}
/// Closed addressing-------------------------------------------------------

int main()
{
    usage_close_hash();
}