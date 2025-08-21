#pragma once
#include <fmt/base.h>
#include <vector>

namespace star {
/** ObjectVector
 *
 * std::vector, but automatically calls release() and retain() on its elements whenever needed
 */
template <class T> class ObjectVector : std::vector<T> {
public:
  using std::vector<T>::begin;
  using std::vector<T>::end;
  using std::vector<T>::size;
  using std::vector<T>::at;
  using std::vector<T>::operator[];

  ~ObjectVector() {
    clear();
  }

  /**
   * Add an element to the vector
   *
   * Retains the object
   */
  virtual void push_back(T object) {
    object->retain();
    std::vector<T>::push_back(object);
  }
  /**
   * Pop and release the last element in the vector
   */
  virtual void pop_back() {
    std::vector<T>::back()->release();
    std::vector<T>::pop_back();
  }
  /**
   * Clear the entire vector and release all objects
   */
  virtual void clear() {
    for (T obj : *this) {
      obj->release();
    }
    std::vector<T>::clear();
  }
  /**
   * Erase an object from a position and release it
   */
  virtual void erase(typename std::vector<T>::iterator position) {
    (*position)->release();

    std::vector<T>::erase(position);
  }
  /**
   * Get a std::vector equivalent of the current vector
   */
  virtual std::vector<T> vector() {
    std::vector<T> vec;
    for (T obj : *this) {
      vec.push_back(obj);
    }

    return vec;
  }
};
} // namespace star
