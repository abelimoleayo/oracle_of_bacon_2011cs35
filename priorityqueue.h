#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

/**
 * The PriorityQueue is a pure virtual (abstract) interface of a priority
 * queue for priority-type P and key-type V.  Priority queue implementations 
 * should inherit from and implement this interface.
 */
template <typename P, typename V>
class PriorityQueue {
  public:
    virtual ~PriorityQueue() { };      // An empty virtual destructor.
                                       // Put an item into the priority queue.
    virtual void insert(P priority, V value) = 0;
    virtual V    removeMin() = 0;      // Remove and return value of min item.
    virtual V    getMin() = 0;         // Returns (but does not remove) min.
    virtual P    getMinPriority() = 0; // Returns min item's priority.
    virtual int  getSize() = 0;        // Returns current number of items.
    virtual bool isEmpty() = 0;        // Returns true if the queue is empty.
};

#endif  // PRIORITYQUEUE_H_
