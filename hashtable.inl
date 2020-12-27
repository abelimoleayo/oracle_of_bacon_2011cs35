/* Author: Imoleayo Abel
 * CS35 Lab 11
 * November 21, 2011
 */

#include <string>
#include <stdexcept>

#include "list.h"
#include "circulararraylist.h"
#include "pair.h"
#include "iterator.h"
#include "queuebasediterator.h"


template <typename K, typename V> 
const double HashTable<K,V>::MAX_LOAD_FACTOR = 0.8;

template <typename K, typename V>
HashTable<K,V>::HashTable(int capacity) {
  this->capacity = capacity;
  this->size = 0;
  this->table = new CircularArrayList<Pair<K,V> >[capacity];
}

template <typename K, typename V>
HashTable<K,V>::~HashTable() {
  delete [] table;
}

template <typename K, typename V>
void HashTable<K,V>::put(K key, V value) {
  int pos = hash(key, capacity);
  for (int i = 0; i < table[pos].getSize(); ++i) {  // Replaces key-value pair
    Pair<K,V> listVal = table[pos][i];              // if it was already in the
    if (listVal.first == key) {                     // hash table.
      table[pos][i] = Pair<K,V>(key,value);
      return;
    }
  }

  ++size;
  table[pos].insertAtTail(Pair<K,V>(key,value));  // Otherwise insert as usual.
  if (getLoadFactor() > MAX_LOAD_FACTOR) {
    expandCapacity();
  }
}

template <typename K, typename V>
V HashTable<K,V>::get(K key) {
  int pos = hash(key, capacity);
  for (int i = 0; i < table[pos].getSize(); ++i) {  // Returns value if key
    Pair<K,V> listVal = table[pos][i];              // is in hash table.
    if (listVal.first == key) { 
      return listVal.second;
    }
  }
  
  throw std::runtime_error("get called on key not in hash table");
}

template <typename K, typename V>
V HashTable<K,V>::remove(K key) {
  int pos = hash(key, capacity);
  for (int i = 0; i < table[pos].getSize(); ++i) {  // Finds key
    Pair<K,V> listVal = table[pos][i];              // if it was already in the
    if (listVal.first == key) {                     // hash table.
      table[pos].removeItem(i);
      --size;
      return listVal.second;
    }
  }

  throw std::runtime_error("remove called on key not in hash table");
}

template <typename K, typename V>
int HashTable<K,V>::getSize() {
  return size;
}

template <typename K, typename V>
bool HashTable<K,V>::isEmpty() {
  return size == 0;
}

template <typename K, typename V>
bool HashTable<K,V>::containsKey(K key) {
 int pos = hash(key, capacity);
  for (int i = 0; i < table[pos].getSize(); ++i) {  // Finds key
    Pair<K,V> listVal = table[pos][i];              // if it was already in the
    if (listVal.first == key) {                     // hash table.
      return true;
    }
  }

  return false;
}

template <typename K, typename V>
bool HashTable<K,V>::containsValue(V value) {
  for (int pos = 0; pos < capacity; ++pos) {
    for (int i = 0; i < table[pos].getSize(); ++i) {  // Finds value
      Pair<K,V> listVal = table[pos][i];              // if it is in the
      if (listVal.second == value) {                  // hash table.
        return true;
      }
    }
  }

  return false;
}


template <typename K, typename V>
List<K>* HashTable<K,V>::getKeys() {
  List<K>* keys = new CircularArrayList<K>;
  for (int pos = 0; pos < capacity; ++pos) {
    for (int i = 0; i < table[pos].getSize(); ++i) {  // Puts all keys on
      Pair<K,V> listVal = table[pos][i];              // the list.
      keys->insertAtTail(listVal.first);
    }
  }
  
  return keys;
}

template <typename K, typename V>
List<V>* HashTable<K,V>::getValues() {
  List<V>* values = new CircularArrayList<V>;
  for (int pos = 0; pos < capacity; ++pos) {
    for (int i = 0; i < table[pos].getSize(); ++i) {  // Puts all values on
      Pair<K,V> listVal = table[pos][i];              // the list.
      values->insertAtTail(listVal.second);
    }
  }
  
  return values;
}

template <typename K, typename V>
Iterator<Pair<K,V> >* HashTable<K,V>::getIterator() {
  QueueBasedIterator<Pair<K,V> >* iter = new QueueBasedIterator<Pair<K,V> >;
  for (int pos = 0; pos < capacity; ++pos) {
    for (int i = 0; i < table[pos].getSize(); ++i) {  // Puts all K-V pairs 
      Pair<K,V> listVal = table[pos][i];              // into the iterator.
        iter->insert(listVal);
    }
  }
  
  return iter;
}

template <typename K, typename V>
int HashTable<K,V>::hash(int key, int capacity) {
  int rv = key % capacity;
  if (rv < 0) {      // Ensuring that our return value is positive, because
    rv += capacity;  // mod in C++ can return a negative value.
  }
  return rv;
}

template <typename K, typename V>
int HashTable<K,V>::hash(std::string key, int capacity) {
  int total = 0;
  for (int i = 0; i < key.length(); ++i) {
    total = 31*total + key[i];
  }
  int rv = total % capacity;
  if (rv < 0) {      // Ensuring that our return value is positive, because
    rv += capacity;  // mod in C++ can return a negative value.
  }
  return rv;
}

template <typename K, typename V>
int HashTable<K,V>::hash(std::string* key, int capacity) {
  std::string keyVal = *key;
  return hash(keyVal,capacity);
}

template <typename K, typename V>
double HashTable<K,V>::getLoadFactor() {
  return size / (double) capacity;
}

template <typename K, typename V>
void HashTable<K,V>::expandCapacity() {
  int oldCapacity = capacity;
  capacity = 2*capacity + 1;   // It might be better to make sure that
                               // the new capacity is prime...
  CircularArrayList<Pair<K,V> >* newTable 
        = new CircularArrayList<Pair<K,V> >[capacity];
  for (int pos = 0; pos < oldCapacity; ++pos) {
    for (int i = 0; i < table[pos].getSize(); ++i) {  // Puts all values into
      Pair<K,V> listVal = table[pos][i];              // the new table.
      int newPos = hash(listVal.first, capacity);
      newTable[newPos].insertAtTail(listVal);
    }
  }
  delete [] table;
  table = newTable;
}
