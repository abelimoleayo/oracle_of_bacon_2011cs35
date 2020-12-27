/* Author: Imoleayo Abel
 * CS35 Lab 11
 * November 21, 2011
 *
 * This implementation is updated to support Dijktra's Algroithm; thus, when a
 * value already on the heap is inserted, its priority is updated to the 
 * priority of the nely inserted copy
 */

#include <algorithm>
#include <stdexcept>

/**
 * Constructs a binary heap with some arbitrary initial capacity.
 */
template <typename P, typename V>
BinaryHeap<P,V>::BinaryHeap() {
  capacity = 10;
  size = 0;
  items = new Pair<P,V>[capacity];
}

/**
 * Creates a BinaryHeap from another instance of a binary heap.
 */
template <typename P, typename V>
BinaryHeap<P,V>::BinaryHeap(const BinaryHeap<P,V>& src) {
  this->capacity = src.capacity;
  this->size = src.size;
  this->items = new Pair<P,V>[capacity];
  for (int i = 0; i < capacity; i++) {
    this->items[i] = src.items[i];
  }
}

/**
 * Frees any memory allocated by this binary heap.
 */
template <typename P, typename V>
BinaryHeap<P,V>::~BinaryHeap() {
  delete [] items;
}
                                   
/**
 * Inserts a new priority-value pair into this binary heap.
 */
template <typename P, typename V>
void BinaryHeap<P,V>::insert(P priority, V value) {
  for (int i = 0; i < size; i++) {      // replace priority of value if value is
    if (items[i].second == value) {     // already on the heap
      items[i].first = priority;
      int parentPos = getParent(i);
      if (priority < items[parentPos].first) {
        bubbleUp(i);
      } else {
        bubbleDown(i);
      }
      return;
    }
  }
  if (size == capacity) {
    expandCapacity();
  }
  items[size++] = Pair<P,V>(priority, value);
  bubbleUp(size-1);
}

/**
 * Removes and returns the minimum item from this binary heap.  Throws a 
 * runtime_error if this binary heap is empty.
 */
template <typename P, typename V>
V BinaryHeap<P,V>::removeMin() {
  if (isEmpty()) {
    throw std::runtime_error("BinaryHeap::removeMin called on an empty heap.");
  }
  V rv = items[0].second;
  items[0] = items[size-1];
  --size;
  bubbleDown(0);
  return rv;
}

/**
 * Returns but does not remove the value of the minimum item from this binary 
 * heap.  Throws a runtime_error if this binary heap is empty.
 */
template <typename P, typename V>
V BinaryHeap<P,V>::getMin() {
  if (isEmpty()) {
    throw std::runtime_error("BinaryHeap::removeMin called on an empty heap.");
  }
  return items[0].second;
}

/**
 * Returns the priority of the minumum item in this binary heap.  Throws a
 * runtime_error if this binary heap is empty.
 */
template <typename P, typename V>
P BinaryHeap<P,V>::getMinPriority() {
  if (isEmpty()) {
    throw std::runtime_error("BinaryHeap::removeMin called on an empty heap.");
  }
  return items[0].first;
}


/**
 * Returns the number of items currently stored in this binary heap.
 */
template <typename P, typename V>
int BinaryHeap<P,V>::getSize() {
  return size;
}

/**
 * Returns true if this binary heap is currently empty, and false otherwise.
 */
template <typename P, typename V>
bool BinaryHeap<P,V>::isEmpty() {
  return size == 0;
}

/**
 * Given an integer position of an item in the heap's array, restores the heap
 * order by recursively bubbling up the item at that position into the 
 * correct position in the heap.
 */
template <typename P, typename V>
void BinaryHeap<P,V>::bubbleUp(int currentPos) {
  if (currentPos == 0) {
    return;
  }
  int parent = getParent(currentPos);
  if (items[parent].first > items[currentPos].first) {
    std::swap(items[parent], items[currentPos]);
    bubbleUp(parent);
  }
}


/**
 * Given an integer position of an item in the heap's array, restores the heap
 * order by recursively bubbling down the item at that position into the 
 * correct position in the heap.
 */
template <typename P, typename V>
void BinaryHeap<P,V>::bubbleDown(int currentPos) {
  if (isLeaf(currentPos)) {
    return;
  }
  int min = getLeft(currentPos);
  if (getRight(currentPos) < size && 
      items[getRight(currentPos)].first < items[min].first) {
    min = getRight(currentPos);
  }
  if (items[currentPos].first > items[min].first) {
    std::swap(items[min], items[currentPos]);
    bubbleDown(min);
  }
}

/**
 * Given an integer position of an item in the heap's array, returns the
 * position of that item's left child in the heap.  The position of the
 * left child is always returned, even if the left child does not currently
 * contain an item.
 */
template <typename P, typename V>
int BinaryHeap<P,V>::getLeft(int pos) {
  return 2*pos + 1;
}

/**
 * Given an integer position of an item in the heap's array, returns the
 * position of that item's right child in the heap.  The position of the
 * right child is always returned, even if the right child does not currently
 * contain an item.
 */
template <typename P, typename V>
int BinaryHeap<P,V>::getRight(int pos) {
  return 2*pos + 2;
}

/**
 * Given an integer position of an item in the heap's array, returns the
 * position of that item's parent in the heap. 
 */
template <typename P, typename V>
int BinaryHeap<P,V>::getParent(int pos) {
  return (pos-1)/2;
}

/**
 * Given an integer position of an item in the heap's array, returns true
 * if that item is a leaf in the heap, and false otherwise.
 */
template <typename P, typename V>
bool BinaryHeap<P,V>::isLeaf(int currentPos) {
  return getLeft(currentPos) >= size;
}

/**
 * Expands the capacity of the array storing the heap, to store more items
 * when needed.
 */
template <typename P, typename V>
void BinaryHeap<P,V>::expandCapacity() {
  capacity = 2*capacity + 1;
  Pair<P,V>* newItems = new Pair<P,V>[capacity];
  for (int i = 0; i < size; ++i) {
    newItems[i] = items[i];
  }
  delete [] items;
  items = newItems;
}

