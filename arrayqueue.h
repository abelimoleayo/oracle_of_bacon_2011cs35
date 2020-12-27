#ifndef ARRAYQUEUE_H_
#define ARRAYQUEUE_H_

#include "queue.h"
#include "circulararraylist.h"

/**
 * ArrayQueue is a ArrayList-based implementation of the Queue interface.
 * It should support O(1) time performance for all operations.
 */
template <typename T>
class ArrayQueue : public Queue<T> {
  private:
    CircularArrayList<T> items;

  public:
    ArrayQueue();
    ~ArrayQueue();

    void enqueue(T item);
    T dequeue();
    int getSize();
    bool isEmpty();
    T getFront();
};

#include "arrayqueue.inl"

#endif
