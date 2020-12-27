#ifndef ITERATOR_H_
#define ITERATOR_H_

/**
 * Defines an abstract Iterator type, which allows the user to iterate over
 * some collection of data.
 */
template <typename T>
class Iterator {
  public:
    virtual ~Iterator() {};
    virtual bool hasNext() = 0;  // Returns true if iterator has more items.
    virtual T getNext() = 0;     // Returns the next item for this iterator.
};

#endif
