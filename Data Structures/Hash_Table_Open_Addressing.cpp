/// Open addressing---------------------------------------------------------
#include <iostream>
#include <vector>
#include <iomanip>
#include <list>
#include <cassert>

/// This class implements open addressing hash table, with Linear Probing.
template< typename ValueType,
    typename HashFunctionType,
    typename MappingFunctionType >
class LinearProbingHashTable
{
private:
    typedef ValueType value_type;

    typedef HashFunctionType hash_function_type;

    typedef MappingFunctionType mapping_function_type;

    typedef std::vector< value_type > table_type;

    typedef std::vector< bool > flags_type;

    /// Array of the stored values.
    table_type table;

    /// Boolean array, identifying if certain entry is present or not.
    flags_type is_occupied;

    /// The hash function, used to convert values into unsigned integers.
    hash_function_type hash_func;

    /// The mapping function, used to convert unsigned integers into values 
    /// of range [0, m).
    mapping_function_type mapping_func;

public:
    /// Constructor
    explicit LinearProbingHashTable(int m_ = 17,
        const hash_function_type& hash_func_ = hash_function_type(),
        const mapping_function_type& mapping_func_ = mapping_function_type())
        : table(m_),
        is_occupied(m_, false),
        hash_func(hash_func_),
        mapping_func(mapping_func_)
    {
        mapping_func.m = m_;
    }

    /// Returns count of buckets in the table.
    unsigned int m() const
    {
        return (unsigned int)table.size();
    }

    /// Returns number of entries in the table.
    unsigned int size() const
    {
        return std::count(is_occupied.cbegin(), is_occupied.cend(), true);
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
    mapping_function_type& mapping_f()
    {
        return mapping_func;
    }
    const mapping_function_type& mapping_f() const
    {
        return mapping_func;
    }

    /// Prints content of this table into 'ostr'.
    /// Together with every value, prints it's original cell.
    void print_detailed(std::ostream& ostr) const {
        for (unsigned int i = 0; i < m(); ++i) {
            ostr << std::setw(4) << i << ": ";
            if (is_occupied[i]) {
                unsigned int value_hash = hash_func(table[i]);
                unsigned int value_cell = mapping_func(value_hash);
                ostr << table[i] << " - (" << value_cell << ")";
            }
            ostr << std::endl;
        }
        ostr << "----------" << std::endl;
    }

    /// Prints state of this table, only by marking occupied cells.
    void print_brief(std::ostream& ostr, unsigned int line = 50) const {
        for (unsigned int i = 0; i < m(); ++i) {
            if (i % line == 0)
                ostr << std::setw(4) << i << ": |";
            ostr.put(is_occupied[i] ? '*' : ' ');
            if ((i + 1) % line == 0)
                ostr << "|" << std::endl;
        }
        ostr << std::endl;
        ostr << "----------" << std::endl;
    }

    /// Inserts 'new_value' in the table.
    void insert_slow(const value_type& new_value) {
        unsigned int value_hash = hash_func(new_value);
        unsigned int value_cell = mapping_func(value_hash);
        // Search for next empty cell
        while (is_occupied[value_cell])
            value_cell = (value_cell + 1) % m();  // Possibly reset on every step
        // Place it there
        table[value_cell] = new_value;
        is_occupied[value_cell] = true;
    }

    /// Inserts 'new_value' in the table.
    void insert_faster(const value_type& new_value) {
        unsigned int value_hash = hash_func(new_value);
        unsigned int value_cell = mapping_func(value_hash);
        // Search for next empty cell
        while (is_occupied[value_cell]) {
            ++value_cell;
            if (value_cell == m())  // Check for need to reset
                value_cell = 0;
        }
        // Place it there
        table[value_cell] = new_value;
        is_occupied[value_cell] = true;
    }

    /// Inserts 'new_value' in the table.
    void insert_fast(const value_type& new_value) {
        unsigned int value_hash = hash_func(new_value);
        unsigned int value_cell = mapping_func(value_hash);
        // Search for next empty cell
        //   part 1
        while (value_cell < m() && is_occupied[value_cell])
            ++value_cell;
        //   part 2
        if (value_cell == m()) {
            value_cell = 0;
            while (is_occupied[value_cell])
                ++value_cell;
        }
        assert(!is_occupied[value_cell]);
        // Place it there
        table[value_cell] = new_value;
        is_occupied[value_cell] = true;
    }

    /// Inserts 'new_value' in the table.
    void insert(const value_type& new_value) {
        insert_fast(new_value);
    }

    /// Returns number of occurrences of 'val' in the table.
    unsigned int count(const value_type& val) const {
        unsigned int val_hash = hash_func(val);
        unsigned int val_cell = mapping_func(val_hash);
        // Scan
        unsigned int result = 0;
        while (is_occupied[val_cell]) {
            if (table[val_cell] == val)  // Compare
                ++result;
            ++val_cell;  // Advance to next cell
            if (val_cell == m())
                val_cell = 0;
        }
        assert(!is_occupied[val_cell]);
        return result;
    }

    /// Tests that "a < b <= c" in circle [0, m).
    bool in_between(unsigned int a, unsigned int b, unsigned int c) const {
        if (a <= c)
            return a < b && b <= c;
        else
            return a < b || b <= c;
    }

    /// Returns next position from 'pos'
    unsigned int next_cell(unsigned int pos) const {
        ++pos;
        if (pos == m())
            pos = 0;
        return pos;
    }

    /// Returns the slot to which the value currently residing at 'cell', 
    /// was originally hashed.
    unsigned int original_cell(unsigned int cell) const {
        assert(is_occupied[cell]);
        unsigned int value_hash = hash_func(table[cell]);
        unsigned int value_original_cell = mapping_func(value_hash);
        return value_original_cell;
    }

    /// Removes 'val' from the table, optionally transposing some 
    /// of its subsequence values.
    void remove(const value_type& val) {
        // Find cell which is occupied by 'val'
        unsigned int val_hash = hash_func(val);
        unsigned int val_cell = mapping_func(val_hash);
        while (is_occupied[val_cell] && table[val_cell] != val)
            val_cell = next_cell(val_cell);
        if (!is_occupied[val_cell])
            return;  // No such entry in the table
        assert(table[val_cell] == val);  // Otherwise, we have found 'val'
        // Remove it
        table[val_cell] = value_type();
        is_occupied[val_cell] = false;
        // Search for other values, look-up of which is invalidated
        while (true) {
            assert(!is_occupied[val_cell]);
            unsigned int next_val_place = next_cell(val_cell);
            while (is_occupied[next_val_place]
                && in_between(val_cell, original_cell(next_val_place), next_val_place))
                next_val_place = next_cell(next_val_place);
            if (!is_occupied[next_val_place])
                return;  // Other values are not invalidated
            // We found another value at 'next_val_place', which should be transposed
            assert(!in_between(val_cell, original_cell(next_val_place), next_val_place));
            // Transpose (next_val_place --> val_cell)
            table[val_cell] = std::move(table[next_val_place]);
            table[next_val_place] = value_type();
            is_occupied[val_cell] = true;
            is_occupied[next_val_place] = false;
            // Continue from 'next_val_place'
            val_cell = next_val_place;
        }
        assert(false);  // We should never reach here
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


/// This class performs hash mapping by division method.
class DivisionMapping
{
public:
    /// The modulo
    unsigned int m;

public:
    /// Constructor
    explicit DivisionMapping(unsigned int m_ = 11)
        : m(m_)
    {}

    unsigned int operator()(unsigned int h) const
    {
        return h % m;
    }
};

/// This class performs hash mapping by multiplication method.
class MultiplicationMapping
{
public:
    /// The constant
    double a;

    /// Size of the table
    unsigned int m;

public:
    /// Ctor
    explicit MultiplicationMapping(
        double a_ = 1.0 / sqrt(2.0),
        unsigned int m_ = 11)
        : a(a_), m(m_)
    {}

    unsigned int operator()(unsigned int h) const
    {
        double int_part;
        return (unsigned int)(modf(h * a, &int_part) * m);
    }
};

void usage_open_hash()
{
    std::cout << "Testing open-addressing hash table ..." << std::endl;

    LinearProbingHashTable<
        std::string,
        StringHash,
        DivisionMapping > table_1(17);

    std::cout << "\t adding values ..." << std::endl;
    table_1.insert("abc");
    table_1.insert("xy");
    table_1.insert("story");
    table_1.insert("functor");
    table_1.insert("label");
    table_1.insert("table");
    table_1.insert("window");

    table_1.print_detailed(std::cout);

    std::cout << "\t adding more values ..." << std::endl;
    table_1.insert("sample");
    table_1.insert("door");
    table_1.insert("find");
    table_1.insert("look-up");

    table_1.print_detailed(std::cout);

    std::cout << "\t checking for presence of values ..." << std::endl;
    std::cout << "'cat' ? " << table_1.count("cat") << std::endl;
    std::cout << "'table' ? " << table_1.count("table") << std::endl;
    std::cout << "'strong' ? " << table_1.count("strong") << std::endl;
    std::cout << "'door' ? " << table_1.count("door") << std::endl;

    std::cout << "\t removing values ..." << std::endl;
    table_1.remove("window");

    table_1.print_detailed(std::cout);

    table_1.remove("abc");

    table_1.print_detailed(std::cout);

}

int main()
{
    usage_open_hash();
}