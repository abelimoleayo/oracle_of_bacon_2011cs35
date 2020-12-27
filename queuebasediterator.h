#ifndef QUEUEBASEDITERATOR_H_
#define QUEUEBASEDITERATOR_H_

#include "iterator.h"
#include "arrayqueue.h"

/**
 * A QueueBasedIterator is a templated iterator intended for use by an
 * arbitrary external container class.  The intention is for the 
 * external container class inserts all items into the iterator
 * before making the iterator available for use.
 *
 * In practice, this iterator is a poor design; real data structure 
 * implementations would include their own internal iterator that allows
 * a user to iterate over the container's data without copying the data.
 */
template <typename T>
class QueueBasedIterator : public Iterator<T> {
  private:
    ArrayQueue<T> remainingItems;

  public:
    QueueBasedIterator();
    ~QueueBasedIterator();
    bool hasNext();         // Returns true if this iterator has more items.
    T getNext();            // Returns the next item in this iterator.
    void insert(T item);    // Inserts a new item into this iterator, for use
                            // by an external container class when this iterator
                            // is being created.
};

#include "queuebasediterator.inl"

#endif
