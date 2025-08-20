#pragma once
#include "Object.h"
#include <fmt/base.h>
#include <vector>

namespace star {

template <class T> class ObjectVector : std::vector<T> {
public:
  using std::vector<T>::begin;
  using std::vector<T>::end;
  using std::vector<T>::size;
  using std::vector<T>::at;

  ~ObjectVector() {
    clear();
  }

  virtual void push_back(T object) {
    object->retain();
    std::vector<T>::push_back(object);
  }
  virtual void pop_back() {
    std::vector<T>::back()->release();
    std::vector<T>::pop_back();
  }
  virtual void clear() {
    for (T obj : *this) {
      obj->release();
    }
    std::vector<T>::clear();
  }
  virtual void erase(std::vector<T>::iterator position) {
    (*position)->release();

    std::vector<T>::erase(position);
  }
  virtual std::vector<T> vector() {
    std::vector<T> vec;
    for (T obj : *this) {
      vec.push_back(obj);
    }

    return vec;
  }
};
} // namespace star
