#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>

#include "dictionary.h"
#include "list.h"
#include "circulararraylist.h"
#include "iterator.h"
#include "pair.h"

template <typename K, typename V>
class HashTable : public Dictionary<K,V> {
  private:
    CircularArrayList<Pair<K,V> >* table;       // The hash table data, with
                                                // each entry in the array 
                                                // storing a list of key-value
                                                // pairs.
    int size;                                   // The number of items currently
                                                // stored in the hash table.
    int capacity;                               // The current size of the
                                                // table array.

    static const double MAX_LOAD_FACTOR;        // Should expand hash table if
                                                // we exceed this load factor.

  public:
    HashTable(int capacity=53);           // Constructs hash table with default
                                          // capacity of 53.
    ~HashTable();
    void     put(K key, V value);         // Inserts key and value into the hash
                                          // table, replacing the old value if
                                          // the key was already in the table.
    V        get(K key);                  // Returns the value for a key in the
                                          // hash table, or throws runtime_error
                                          // if the key is not present.
    V        remove(K key);               // Removes a key-value pair from the
                                          // hash table, or throws runtime_error
                                          // if the key is not present.
    int      getSize();                   // Returns number of items in table.
    bool     isEmpty();                   // Returns if the table is empty.
    bool     containsKey(K key);          // Returns true if the hash table
                                          // contains the given key.
    bool     containsValue(V value);      // Returns true if the hash table 
                                          // contains the given value.
    List<K>* getKeys();                   // Returns all keys in the table.
    List<V>* getValues();                 // Returns all values in the table.
    Iterator<Pair<K,V> >* getIterator();  // Returns a pointer to an iterator
                                          // for all K-V pairs in the table.

  private:
    int hash(int key, int capacity);          // Returns a hash code for the
                                              // given integer.
    int hash(std::string key, int capacity);  // Returns a hash code for the
                                              // given string.
    int hash(std::string* key, int capacity); // Returns a hash code for the
                                              // given string pointer
    double getLoadFactor();                   // Returns the current load factor
                                              // of the hash table.
    void expandCapacity();                    // Expands the capacity of the
                                              // hash table's array.
};

#include "hashtable.inl"

#endif
