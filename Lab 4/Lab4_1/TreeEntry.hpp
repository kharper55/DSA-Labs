#ifndef TREE_ENTRY_HPP
#define TREE_ENTRY_HPP

template <typename K, typename V>
class Entry {						// a (key, value) pair
    public:						// public types
        typedef K Key;					// key type
        typedef V Value;					// value type
    public:						// public functions
        Entry(const K& k = K(), const V& v = V())		// constructor
            : _key(k), _value(v) { }	
        const K& key() const { return _key; }		// get key (read only)
        const V& value() const { return _value; }		// get value (read only)
        void setKey(const K& k) { _key = k; }		// set key
        void setValue(const V& v) { _value = v; }		// set value
        // Define the equality operator
        bool operator==(const Entry& other) const {
            return value() == other.value();
        }
    private:						// private data
        K _key;						// key
        V _value;					// value
};

#endif // TREE_ENTRY_HPP