#ifndef I2P2_ITERATOR_H
#define I2P2_ITERATOR_H
#include <iterator>
#include "I2P2_def.h"

//#include <iostream>

namespace I2P2 {
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
struct iterator_impl_base {
  virtual reference operator*() const = 0;
  virtual reference operator[](difference_type offset) const = 0;
  virtual pointer operator->() const = 0;
  virtual difference_type operator-(const iterator_impl_base &rhs) const = 0;
  virtual iterator_impl_base &operator++() = 0;
  virtual iterator_impl_base &operator--() = 0;
  virtual iterator_impl_base &operator+=(difference_type offset) = 0;
  virtual iterator_impl_base &operator-=(difference_type offset) = 0;
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
   virtual Node* getNode() const=0;
   virtual size_type getIdx() const=0;
   virtual const pointer* getPtrofPtr()const=0;
   virtual iterator_impl_base* clone() const = 0;
   //!!!
};

class vector_iterator : public iterator_impl_base {
 protected:
  // You may want to declare what your vector_iterator stores here
  pointer* ptrofptr;//!!!
  size_type idx;

 public:
  vector_iterator();
  vector_iterator(pointer*, size_type);
  iterator_impl_base &operator++();
  iterator_impl_base &operator--();
  iterator_impl_base &operator+=(difference_type offset);
  iterator_impl_base &operator-=(difference_type offset);
  bool operator==(const iterator_impl_base &rhs) const;
  bool operator!=(const iterator_impl_base &rhs) const;
  bool operator<(const iterator_impl_base &rhs) const;
  bool operator>(const iterator_impl_base &rhs) const;
  bool operator<=(const iterator_impl_base &rhs) const;
  bool operator>=(const iterator_impl_base &rhs) const;
  difference_type operator-(const iterator_impl_base &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;

  Node* getNode() const{return nullptr;}
  size_type getIdx() const{return this->idx;}
  const pointer* getPtrofPtr()const{return this->ptrofptr;}
  iterator_impl_base* clone() const { return new vector_iterator(ptrofptr, idx);}
};

class list_iterator : public iterator_impl_base {
 protected:
  // You may want to declare what your list_iterator stores here
  	
 	Node* node; //!!!
 public:
  list_iterator();
  list_iterator(Node*);//!!!
  iterator_impl_base &operator++();
  iterator_impl_base &operator--();
  iterator_impl_base &operator+=(difference_type offset);
  iterator_impl_base &operator-=(difference_type offset);
  bool operator==(const iterator_impl_base &rhs) const;
  bool operator!=(const iterator_impl_base &rhs) const;
  bool operator<(const iterator_impl_base &rhs) const;
  bool operator>(const iterator_impl_base &rhs) const;
  bool operator<=(const iterator_impl_base &rhs) const;
  bool operator>=(const iterator_impl_base &rhs) const;
  difference_type operator-(const iterator_impl_base &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;
  
  //!!!
	Node* getNode() const {return this->node;}
  size_type getIdx() const{return 0;}
  const pointer* getPtrofPtr()const{return nullptr;}
	iterator_impl_base* clone() const { return new list_iterator(node); }
  size_type getPos(Node* n) const{
    size_type pos=0;
    Node* nodeit=n;
    while(nodeit->isHead!=true){
      pos++;
      nodeit=nodeit->prev;
    }
    //std::cout<<"pos:"<<pos<<std::endl;
    return pos;
  }
};

class const_iterator {
 public:
  using difference_type = I2P2::difference_type;
  using value_type = I2P2::value_type;
  using pointer = I2P2::const_pointer;
  using reference = I2P2::const_reference;
  using iterator_category = std::random_access_iterator_tag;

 protected:
  iterator_impl_base *p_;

 public:
  ~const_iterator();
  const_iterator();
  const_iterator(const const_iterator &rhs);
  const_iterator(iterator_impl_base *p);
  const_iterator &operator=(const const_iterator &rhs);
  const_iterator &operator++();
  const_iterator operator++(int);
  const_iterator &operator--();
  const_iterator operator--(int);
  const_iterator &operator+=(difference_type offset);
  const_iterator operator+(difference_type offset) const;
  const_iterator &operator-=(difference_type offset);
  const_iterator operator-(difference_type offset) const;
  difference_type operator-(const const_iterator &rhs) const;
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
   Node* getNode()const{return p_->getNode();}
   size_type getIdx()const{return p_->getIdx();};
   const pointer* getPtrofPtr()const{return p_->getPtrofPtr();}
};

class iterator : public const_iterator {
 public:
  using difference_type = I2P2::difference_type;
  using value_type = I2P2::value_type;
  using pointer = I2P2::pointer;
  using reference = I2P2::reference;
  using iterator_category = std::random_access_iterator_tag;

 public:
  iterator();
  iterator(iterator_impl_base *p);
  iterator(const iterator &rhs);
  iterator &operator++();
  iterator operator++(int);
  iterator &operator--();
  iterator operator--(int);
  iterator &operator+=(difference_type offset);
  iterator operator+(difference_type offset) const;
  iterator &operator-=(difference_type offset);
  iterator operator-(difference_type offset) const;
  difference_type operator-(const iterator &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;
  
  //Node* getNode() const {return p_->getNode();}//!!!
  //pointer getPtrofPtr()const{return p_->getPtrofPtr();}
};
}  // namespace I2P2

#endif

