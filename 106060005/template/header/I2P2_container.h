#ifndef I2P2_CONTAINER_H
#define I2P2_CONTAINER_H
#include "I2P2_def.h"
#include "I2P2_iterator.h"

namespace I2P2 {

template <typename value_type>
class iterator;

template <typename value_type>
class const_iterator;

template <typename value_type>
struct container_base {

  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;

  virtual bool empty() const = 0;
  virtual size_type size() const = 0;
};

template <typename value_type>
struct dynamic_size_container : container_base<value_type> {

  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;

  virtual iterator<value_type> begin() = 0;
  virtual const_iterator<value_type> begin() const = 0;
  virtual iterator<value_type> end() = 0;
  virtual const_iterator<value_type> end() const = 0;
  virtual void clear() = 0;
  virtual void erase(const_iterator<value_type> pos) = 0;
  virtual void erase(const_iterator<value_type> begin, const_iterator<value_type> end) = 0;
  // The following need only be defined for vector
  virtual void reserve(size_type new_capacity) {} 
  virtual void shrink_to_fit() {}
  virtual size_type capacity() const { return this->size(); }
};

template <typename value_type>
struct ordered_container : dynamic_size_container<value_type> {

  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;

  virtual reference back() = 0;
  virtual const_reference back() const = 0;
  virtual reference front() = 0;
  virtual const_reference front() const = 0;
  virtual void insert(const_iterator<value_type> pos, size_type count, const_reference val) = 0;
  virtual void insert(const_iterator<value_type> pos, const_iterator<value_type> begin, const_iterator<value_type> end) = 0;
  virtual void pop_back() = 0;
  virtual void pop_front() = 0;
  virtual void push_back(const_reference val) = 0;
  virtual void push_front(const_reference val) = 0;
};

template <typename value_type>
struct randomaccess_container : ordered_container<value_type> {

  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;

  virtual reference operator[](size_type pos) = 0;
  virtual const_reference operator[](size_type pos) const = 0;
};
}  // namespace I2P2

#endif

/* This file should not be modified 
 * You Vector and List will be derived from these containers */

