#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include "priorityqueue.h"
#include "pair.h"

/**
 * The BinaryHeap is a pure virtual (abstract) interface of a priority
 * queue for priority-type P and key-type V.  
 *
 * This implementation is updated to support Dijktra's Algorithm; thus, when a
 * value already on the heap is inserted, its priority is updated to the 
 * priority of the newly inserted copy
 */
template <typename P, typename V>
class BinaryHeap : public PriorityQueue<P,V> {
  private:
    Pair<P,V>* items;
    int size;
    int capacity;

  public:
    BinaryHeap();                            // The default constructor.
    BinaryHeap(const BinaryHeap<P,V>& src);  // A copy constructor.
    ~BinaryHeap(); 
                                   
    void insert(P priority, V value);  // Put an item into the heap.
    V    removeMin();                  // Remove and return value of min item.
    V    getMin();                     // Returns (but does not remove) min.
    P    getMinPriority();             // Returns min item's priority.
    int  getSize();                    // Returns current number of items.
    bool isEmpty();                    // Returns true if the heap is empty.
    
  private:
    void bubbleUp(int currentPos);     // Bubbles a position up in the heap to
                                       // restore the heap-order property.
    void bubbleDown(int currentPos);   // Bubbles a position down in the heap
                                       // to restore the heap-order property.
    int getLeft(int pos);              // Returns left pos for a given pos.
    int getRight(int pos);             // Returns right pos for a given pos.
    int getParent(int pos);            // Returns parent pos for a given pos.
    bool isLeaf(int pos);              // Returns if the position is a leaf.
    void expandCapacity();             // Expands the capacity of this heap.
};

#include "binaryheap.inl"
#endif  // BINARYHEAP_H_
