#ifndef I2P2_VECTOR_H
#define I2P2_VECTOR_H
#include "I2P2_container.h"
#include "I2P2_iterator.h"


namespace I2P2 {

template <typename value_type>
class Vector : public randomaccess_container<value_type> {
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
 private:
  // you may want to declare the necessary members for your Vector here
  pointer* begin_;
  pointer* last_;
  pointer* end_;

  /* The following are standard methods from the STL
   * If you are not sure what they do
   * look them up and implement your own version */
 public:
  //typedef typename Vector<value_type>::iterator iterator;
  using iterator = I2P2::iterator<value_type> ;
  using const_iterator = I2P2::const_iterator<value_type> ;
  
  ~Vector();
  Vector();
  Vector(const Vector &rhs);
  Vector &operator=(const Vector &rhs);
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  size_type capacity() const;
  size_type size() const;
  void clear();
  bool empty() const;
  //template<>
  void erase(const_iterator pos);
  void erase(const_iterator begin, const_iterator end);
  void insert(const_iterator pos, size_type count, const_reference val);
  void insert(const_iterator pos, const_iterator begin, const_iterator end);
  void pop_back();
  void pop_front();
  void push_back(const_reference val);
  void push_front(const_reference val);
  void reserve(size_type new_capacity);
  void shrink_to_fit();
};
}
  // namespace I2P2
#include "../src/I2P2_Vector.cpp"

#endif

