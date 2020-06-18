#ifndef I2P2_LIST_H
#define I2P2_LIST_H
#include "I2P2_container.h"
#include "I2P2_iterator.h"

namespace I2P2 {

template<typename value_type>
struct Node;

template <typename value_type>
class List : public ordered_container<value_type> {
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
 protected:
  // you may want to declare necessary members for your List container here
	//!!!
	//Node* head;
  Node<value_type>* head;
	Node<value_type>* tail;
	size_type _size;
	
  /* The following are standard methods from the STL
   * If you are not sure what they do
   * look them up and implement your own version */
 public:
  using iterator = I2P2::iterator<value_type> ;
  using const_iterator = I2P2::const_iterator<value_type> ;
  ~List();
  List();
  List(const List &rhs);
  List &operator=(const List &rhs);
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  size_type size() const;
  void clear();
  bool empty() const;
  void erase(const_iterator pos);
  void erase(const_iterator begin, const_iterator end);
  void insert(const_iterator pos, size_type count, const_reference val);
  void insert(const_iterator pos, const_iterator begin, const_iterator end);
  void pop_back();
  void pop_front();
  void push_back(const_reference val);
  void push_front(const_reference val);
};
}  // namespace I2P2

#include "../src/I2P2_List.cpp"

#endif

