/* Author: Imoleayo Abel
 * CS35 Lab 11
 * November 21, 2011
 */

#include "queue.h"

template <typename T>
QueueBasedIterator<T>::QueueBasedIterator() {
}

template <typename T>
QueueBasedIterator<T>::~QueueBasedIterator() {
}

/**
 * Returns true if the iterator has a next item, and false if all items
 * have already been iterated over.
 */
template <typename T>
bool QueueBasedIterator<T>::hasNext() {
  return !remainingItems.isEmpty();
}

/**
 * Returns the next item in the iterator.
 */
template <typename T>
T QueueBasedIterator<T>::getNext() {
  return remainingItems.dequeue();
}

/**
 * Stores an item in the iterator for later iteration.  This is a 
 * non-Iterator function intended for use by an external data structure
 * that builds the iterator.
 */
template <typename T>
void QueueBasedIterator<T>::insert(T item) {
  remainingItems.enqueue(item);
}
