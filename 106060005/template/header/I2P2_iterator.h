#ifndef I2P2_ITERATOR_H
#define I2P2_ITERATOR_H
#include <iterator>
#include "I2P2_def.h"

//#include <iostream>

namespace I2P2 {

template <typename value_type>
struct Node{
	value_type data;
	Node* next;
	Node* prev;
  bool isHead;
  bool isTail;
	Node(value_type data){
		this->data=data; this->next=nullptr; this->prev=nullptr;
    this->isHead=false; this->isTail=false;
 	}
};//!!!

template <typename value_type>
struct iterator_impl_base {
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;

  virtual reference operator*() const = 0;
  virtual reference operator[](difference_type offset) const = 0;
  virtual pointer operator->() const = 0;
  virtual difference_type operator-(const iterator_impl_base &rhs) const = 0;
  virtual iterator_impl_base<value_type> &operator++() = 0;
  virtual iterator_impl_base<value_type> &operator--() = 0;
  virtual iterator_impl_base<value_type> &operator+=(difference_type offset) = 0;
  virtual iterator_impl_base<value_type> &operator-=(difference_type offset) = 0;
  virtual bool operator==(const iterator_impl_base &rhs) const = 0;
  virtual bool operator!=(const iterator_impl_base &rhs) const = 0;
  virtual bool operator<(const iterator_impl_base &rhs) const = 0;
  virtual bool operator>(const iterator_impl_base &rhs) const = 0;
  virtual bool operator<=(const iterator_impl_base &rhs) const = 0;
  virtual bool operator>=(const iterator_impl_base &rhs) const = 0;
  /* This is the base class of all the container-specialized iterators
   * In order to invoke a derived function from this class
   * you may have to either do a downcast or invoke from a virtual function */
   
   //!!!
   virtual Node<value_type>* getNode() const=0;
   virtual size_type getIdx() const=0;
   virtual const pointer* getPtrofPtr()const=0;
   virtual iterator_impl_base<value_type>* clone() const = 0;
   //!!!
};

template <typename value_type>
class vector_iterator : public iterator_impl_base<value_type> {
  public:
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;

 protected:
  // You may want to declare what your vector_iterator stores here
  pointer* ptrofptr;//!!!
  size_type idx;

 public:
  vector_iterator();
  vector_iterator(pointer*, size_type);
  iterator_impl_base<value_type> &operator++();
  iterator_impl_base<value_type> &operator--();
  iterator_impl_base<value_type> &operator+=(difference_type offset);
  iterator_impl_base<value_type> &operator-=(difference_type offset);
  bool operator==(const iterator_impl_base<value_type> &rhs) const;
  bool operator!=(const iterator_impl_base<value_type> &rhs) const;
  bool operator<(const iterator_impl_base<value_type> &rhs) const;
  bool operator>(const iterator_impl_base<value_type> &rhs) const;
  bool operator<=(const iterator_impl_base<value_type> &rhs) const;
  bool operator>=(const iterator_impl_base<value_type> &rhs) const;
  difference_type operator-(const iterator_impl_base<value_type> &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;

  Node<value_type>* getNode() const{return nullptr;}
  size_type getIdx() const{return this->idx;}
  const pointer* getPtrofPtr()const{return this->ptrofptr;}
  iterator_impl_base<value_type>* clone() const { return new vector_iterator(ptrofptr, idx);}
};

template <typename value_type>
class list_iterator : public iterator_impl_base<value_type> {
 public:
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;

 protected:
  // You may want to declare what your list_iterator stores here
 	Node<value_type>* node; //!!!
 public:
  list_iterator();
  list_iterator(Node<value_type>*);//!!!
  iterator_impl_base<value_type> &operator++();
  iterator_impl_base<value_type> &operator--();
  iterator_impl_base<value_type> &operator+=(difference_type offset);
  iterator_impl_base<value_type> &operator-=(difference_type offset);
  bool operator==(const iterator_impl_base<value_type> &rhs) const;
  bool operator!=(const iterator_impl_base<value_type> &rhs) const;
  bool operator<(const iterator_impl_base<value_type> &rhs) const;
  bool operator>(const iterator_impl_base<value_type> &rhs) const;
  bool operator<=(const iterator_impl_base<value_type> &rhs) const;
  bool operator>=(const iterator_impl_base<value_type> &rhs) const;
  difference_type operator-(const iterator_impl_base<value_type> &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;
  
  //!!!
	Node<value_type>* getNode() const {return this->node;}
  size_type getIdx() const{return 0;}
  const pointer* getPtrofPtr()const{return nullptr;}
	iterator_impl_base<value_type>* clone() const { return new list_iterator(node); }
  size_type getPos(Node<value_type>* n) const{
    size_type pos=0;
    Node<value_type>* nodeit=n;
    while(nodeit->isHead!=true){
      pos++;
      nodeit=nodeit->prev;
    }
    //std::cout<<"pos:"<<pos<<std::endl;
    return pos;
  }
};

template <typename value_type>
class const_iterator {
 public:
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  /*using difference_type = I2P2::difference_type;
  using value_type = I2P2::value_type;
  using pointer = I2P2::const_pointer;
  using reference = I2P2::const_reference;*/
  using iterator_category = std::random_access_iterator_tag;

 protected:
  iterator_impl_base<value_type> *p_;

 public:
  ~const_iterator();
  const_iterator();
  const_iterator(const const_iterator<value_type> &rhs);
  const_iterator(iterator_impl_base<value_type> *p);
  const_iterator<value_type> &operator=(const const_iterator &rhs);
  const_iterator<value_type> &operator++();
  const_iterator<value_type> operator++(int);
  const_iterator<value_type> &operator--();
  const_iterator<value_type> operator--(int);
  const_iterator<value_type> &operator+=(difference_type offset);
  const_iterator<value_type> operator+(difference_type offset) const;
  const_iterator<value_type> &operator-=(difference_type offset);
  const_iterator<value_type> operator-(difference_type offset) const;
  difference_type operator-(const const_iterator<value_type> &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;
  bool operator==(const const_iterator &rhs) const;
  bool operator!=(const const_iterator &rhs) const;
  bool operator<(const const_iterator &rhs) const;
  bool operator>(const const_iterator &rhs) const;
  bool operator<=(const const_iterator &rhs) const;
  bool operator>=(const const_iterator &rhs) const;
  /* This class holds an iterator_impl_base
   * and you may want to have some ways to 
   * invoke a container-specialized method from here
   * for insert/erase methods (look at their parameters if you are not sure) */
   //!!!
   Node<value_type>* getNode()const{return p_->getNode();}
   size_type getIdx()const{return p_->getIdx();};
   const pointer* getPtrofPtr()const{return p_->getPtrofPtr();}
};

template <typename value_type>
class iterator : public const_iterator<value_type> {
 public:
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  /*using difference_type = I2P2::difference_type;
  using value_type = I2P2::value_type;
  using pointer = I2P2::pointer;
  using reference = I2P2::reference;*/
  using iterator_category = std::random_access_iterator_tag;

 public:
  iterator();
  iterator(iterator_impl_base<value_type> *p);
  iterator(const iterator &rhs);
  iterator<value_type> &operator++();
  iterator<value_type> operator++(int);
  iterator<value_type> &operator--();
  iterator<value_type> operator--(int);
  iterator<value_type> &operator+=(difference_type offset);
  iterator<value_type> operator+(difference_type offset) const;
  iterator<value_type> &operator-=(difference_type offset);
  iterator<value_type> operator-(difference_type offset) const;
  difference_type operator-(const iterator &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;
  
  //Node* getNode() const {return p_->getNode();}//!!!
  //pointer getPtrofPtr()const{return p_->getPtrofPtr();}
};
}  // namespace I2P2

#include "../src/I2P2_iterator.cpp"

#endif

