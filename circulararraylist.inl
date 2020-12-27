/* Author: Imoleayo Abel
 * CS35 Lab 11
 * November 21, 2011
 */

#include <stdexcept>

template <typename T>
CircularArrayList<T>::CircularArrayList() {
  headPos = 0;
  size = 0;
  capacity = 0;
  values = new T[capacity];
}

template <typename T>
CircularArrayList<T>::CircularArrayList(const CircularArrayList<T>& src) {
  this->headPos = src.headPos;          // We can directly copy (by value) each
  this->size = src.size;                // piece of  non-pointer data in the 
  this->capacity = src.capacity;        // source list...
  this->values = new T[capacity];       // But we need to allocate our own value
  for (int i = 0; i < capacity; ++i) {  // array on the heap and copy data from
    this->values[i] = src.values[i];    // the source list's values array.
  }
}

template <typename T>
CircularArrayList<T>::~CircularArrayList() {
  delete [] values;
}

template <typename T>
int CircularArrayList<T>::getSize() {
  return size;
}

template <typename T>
bool CircularArrayList<T>::isEmpty() {
  return size == 0;
}

template <typename T>
T CircularArrayList<T>::peekHead() {
  if (isEmpty()) {
    throw std::runtime_error("Attempted to peekHead on an empty list.");
  }
  return values[headPos];
}

template <typename T>
T CircularArrayList<T>::peekTail() {
  if (isEmpty()) {
    throw std::runtime_error("Attempted to peekTail on an empty list.");
  }
  return values[(headPos+size-1)%capacity];
}

template <typename T>
T CircularArrayList<T>::getItem(int i) {
  if (i < 0 || i >= size) {
    throw std::runtime_error("Attempted to getItem out of bounds.");
  }
  return values[(headPos+i)%capacity];
}

template <typename T>
void CircularArrayList<T>::insertAtHead(T value) {
  if (size == capacity) {     // Ensures we have space in the array.
    expandCapacity();
  }
  headPos = (headPos+capacity-1) % capacity;  // Avoids mod of negative #.
  values[headPos] = value;    // Copies the value to the new first position.
  ++size;
}

template <typename T>
void CircularArrayList<T>::insertAtTail(T value) {
  if (size == capacity) {     // Ensures we have space in the array.
    expandCapacity();
  }
  values[(headPos+size)%capacity] = value;
  ++size;
}

template <typename T>
void CircularArrayList<T>::setItem(int i, T value) {
  if (i >= size) {
    throw std::runtime_error("Attempted to setItem at invalid position");
  }
  values[(headPos+i)%capacity] = value;
}

template <typename T>
T CircularArrayList<T>::removeHead() {
  if (isEmpty()) {
    throw std::runtime_error("Attempted to removeHead on an empty list.");
  }

  int oldHeadPos = headPos;        // Store position of value to return
  headPos = (headPos+1)%capacity;  // Resets head to new position
  --size;
  return values[oldHeadPos];
}

template <typename T>
T CircularArrayList<T>::removeTail() {
  if (isEmpty()) {
    throw std::runtime_error("Attempted to removeTail on an empty list.");
  }

  --size;
  return values[(headPos+size)%capacity];  
}

template <typename T>
T CircularArrayList<T>::removeItem(int i) {
  if (i >= size) {
    throw std::runtime_error("Attempted to remove an invalid position in the \
list");
  }

  if (i == 0) {
    return removeHead();      // removeHead is more efficient than this function
  }

  T rv = values[(headPos+i)%capacity];  // Saves the item we're going to return.
  for (int j = i; j < size-1; ++j) {    // Moves items left to fill i's place.
    values[(headPos+j)%capacity] = values[(headPos+j+1)%capacity];
  }
  --size;
  return rv;
}

template <typename T>
T& CircularArrayList<T>::operator[](int i) {
  if (i >= size) {
    throw std::runtime_error("Attempted to access an invalid position in the \
list");
  }
                                        // Returning a reference is exactly
                                        // like returning a regular value, 
                                        // except the value needs to continue
  return values[(headPos+i)%capacity];  // existing after this function returns.
} 

template <typename T>
void CircularArrayList<T>::expandCapacity() {
  int newCapacity = 2*capacity + 1;
  T* newArray = new T[newCapacity];
  for (int i = 0; i < capacity; ++i) {
    newArray[i] = values[(headPos + i) % capacity];
  }
  delete [] values;
  values = newArray;
  headPos = 0;
  capacity = newCapacity;
}
