#include "../header/I2P2_Vector.h"
#include <iostream>
extern bool dbg;
extern bool vcall;

namespace I2P2 {
  
    /* Your definition for the Vector class goes here */
  
	
	template<typename value_type>
  Vector<value_type>::~Vector(){
		if(dbg)std::cout<<"V Des"<<std::endl;
    if(begin_!=nullptr){
      for(size_type i=0; i<capacity(); i++){
        if(begin_[i]!=nullptr)delete begin_[i];
      }
      delete [] begin_;
    }
    begin_=nullptr;
    last_=nullptr;
    end_=nullptr;
  }
	
	template<typename value_type>
  Vector<value_type>::Vector(){
    if(dbg)std::cout<<"V Const"<<std::endl;
    begin_=nullptr;
    last_=nullptr;
    end_=nullptr;
  }
	
	template<typename value_type>
  Vector<value_type>::Vector(const Vector &rhs){
    if(dbg)std::cout<<"V Cpy const"<<std::endl;
    begin_=nullptr;
    last_=nullptr;
    end_=nullptr;
    reserve(rhs.size());

    for(size_type i=0; i<rhs.size(); i++){
      *begin_[i] = rhs[i];
    }
    last_=begin_+rhs.size();
  }
	
	template<typename value_type>
  Vector<value_type>& Vector<value_type>::operator=(const Vector& rhs){
    if(dbg)std::cout<<"V Op="<<std::endl;
    if(this==&rhs)return *this;

    last_=begin_;
    reserve(rhs.size());

    for(size_type i=0; i<rhs.size(); i++){
      *begin_[i]=rhs[i];//rhs[i];
    }
    last_=begin_+rhs.size();

    return *this;
  }
	
	template<typename value_type>
  iterator<value_type> Vector<value_type>::begin(){
    if(dbg)std::cout<<"V it Begin"<<std::endl;
    vector_iterator<value_type> vi(begin_, 0);
    return iterator(&vi);
  }
	
	template<typename value_type>
  const_iterator<value_type> Vector<value_type>::begin() const{
    if(dbg)std::cout<<"V cstit Begin"<<std::endl;
    vector_iterator<value_type> vi(begin_, 0);
    return const_iterator(&vi);
  }
	
	template<typename value_type>
  iterator<value_type> Vector<value_type>::end(){
    if(dbg)std::cout<<"V it End"<<std::endl;
    vector_iterator<value_type> vi(last_, size());
    return iterator(&vi);
  }
	
	template<typename value_type>
  const_iterator<value_type> Vector<value_type>::end() const{
    if(dbg)std::cout<<"V cstit End"<<std::endl;
    vector_iterator<value_type> vi(last_, size());
    return const_iterator(&vi);
  }
	
	template<typename value_type>
  value_type& Vector<value_type>::front(){
    if(dbg)std::cout<<"V Front"<<std::endl;
    return *(*begin_);
  }
	
	template<typename value_type>
  const value_type& Vector<value_type>::front() const{
    if(dbg)std::cout<<"V const Front"<<std::endl;
    return *(*begin_);
  }
	
	template<typename value_type>
  value_type& Vector<value_type>::back(){
    if(dbg)std::cout<<"V back"<<std::endl;
    return *(*(last_-1)); //the element previous of last?
  }
	
	template<typename value_type>
  const value_type& Vector<value_type>::back() const{
    if(dbg)std::cout<<"V Back"<<std::endl;
    return *(*(last_-1)); //the element previous of last?
  }
	
	template<typename value_type>
  value_type& Vector<value_type>::operator[](size_type pos){
     if(dbg||vcall)std::cout<<"V []"<<std::endl;
    return *(begin_[pos]);
  }
	
	template<typename value_type>
  const value_type& Vector<value_type>::operator[](size_type pos) const{
    if(dbg||vcall)std::cout<<"V const[]"<<std::endl;
    return *(begin_[pos]);
  }
	
	template<typename value_type>
  size_type Vector<value_type>::capacity() const{
    if(dbg)std::cout<<"V Cap"<<std::endl;
    return end_-begin_;
  }
	
	template<typename value_type>
  size_type Vector<value_type>::size() const{
    if(dbg)std::cout<<"V Sz"<<std::endl;
    return last_-begin_;
  }
	
	template<typename value_type>
  void Vector<value_type>::clear(){
    if(dbg||vcall)std::cout<<"V Clr"<<std::endl;
    last_=begin_;
  }
	
	template<typename value_type>
  bool Vector<value_type>::empty() const{
    if(dbg)std::cout<<"V empty"<<std::endl;
    return (size()==0);
  }
	
	template<typename value_type>
  void Vector<value_type>::erase(const_iterator pos){
    if(dbg||vcall)std::cout<<"V Erase"<<std::endl;
    size_type tgt = const_cast<value_type**>(pos.getPtrofPtr())-begin_;//= pos.getIdx();
    for(size_type i=tgt; i<size()-1; i++){
      *(begin_[i])=*(begin_[i+1]);
    }
    last_--;
  }
	
	template<typename value_type>
  void Vector<value_type>::erase(const_iterator begin, const_iterator end){
    if(dbg||vcall)std::cout<<"V Erase range"<<std::endl;
    size_type st = const_cast<value_type**>(begin.getPtrofPtr())-begin_;//begin.getIdx()
    size_type ed = const_cast<value_type**>(end.getPtrofPtr())-begin_;//end.getIdx();
    size_type stnow = st;
    size_type ednow = ed;
    while(ednow!=size()){
      *(begin_[stnow])=*(begin_[ednow]);
      ednow++;
      stnow++;
    }
    last_-=ed-st;
    //not sure
  }
	
	template<typename value_type>
  void Vector<value_type>::insert(const_iterator pos, size_type count, const_reference val){
    if(dbg||vcall)std::cout<<"V Insert"<<std::endl;
    size_type tgt = const_cast<value_type**>(pos.getPtrofPtr())-begin_;//pos.getIdx();
    if(vcall)std::cout<<"tgt"<<tgt<<"cnt"<<count<<"sz"<<size()<<"cap"<<capacity()<<std::endl;
    
    if(count>0){
      if(size()+count>=capacity())reserve(std::max(capacity()+count, capacity()+capacity()/2));//>
    
      for(size_type i=size()+count-1; i>=tgt+count; i--){
        *(begin_[i])=*(begin_[i-count]);
      }
      for(size_type i=tgt; i<tgt+count; i++){
        *(begin_[i])=val;
      }
      last_+=count;
    }
    
  }
	
	template<typename value_type>
  void Vector<value_type>::insert(const_iterator pos, 
    const_iterator begin, const_iterator end){
    //std::cout<<"!!!!!!!!!!!!!!!"<<std::endl;
    if(dbg||vcall)std::cout<<"V Insert range"<<std::endl;
    size_type tgt = const_cast<value_type**>(pos.getPtrofPtr())-begin_;// pos.getIdx();
    while(begin!=end){
      if(size()==capacity())reserve(std::max(capacity()+1, capacity()*3));
      
      for(size_type i=size(); i>tgt; i--){
          *(begin_[i])=*(begin_[i-1]);
      }
      *(begin_[tgt])=*begin;
      
      //std::cout<<"IR val:"<<*begin<<"!"<<std::endl;

      last_++;
      begin++;
      tgt++;
    }
    //???
  }
	
	template<typename value_type>
  void Vector<value_type>::pop_back(){
    if(dbg||vcall)std::cout<<"V Pop back"<<std::endl;
    last_--;
  }
	
	template<typename value_type>
  void Vector<value_type>::pop_front(){
    if(dbg||vcall)std::cout<<"V Pop front"<<std::endl;
    for(size_type i=0; i<size()-1; i++){
      *(begin_[i])=*(begin_[i+1]);
    }
    last_--;
  }
	
	template<typename value_type>
  void Vector<value_type>::push_back(const_reference val){
    if(dbg||vcall)std::cout<<"V Push back"<<std::endl;
    if(size()==capacity())reserve(std::max(capacity()+1, capacity()*3));
    *(*last_)=val;
    last_++;
  }
	
	template<typename value_type>
  void Vector<value_type>::push_front(const_reference val){
    if(dbg||vcall)std::cout<<"V Push front"<<std::endl;
    if(size()==capacity())reserve(std::max(capacity()+1, capacity()*3));
    for(size_type i=size(); i>0; i--){
      *(begin_[i])=*(begin_[i-1]);
    }
    *(begin_[0])=val;
    last_++;
  }

  //to do
	
	template<typename value_type>
  void Vector<value_type>::reserve(size_type new_capacity){
    if(dbg||vcall)std::cout<<"V Reserve"<<std::endl;
    if(new_capacity>capacity()){
      pointer* newbegin = new pointer[new_capacity];
      for(size_type i=0; i<size(); i++){
        newbegin[i]=begin_[i];
      }
      for(size_type i=size(); i<new_capacity; i++){
        newbegin[i]=new value_type();
      }

      size_type sz = size();
      if(begin_!=nullptr)delete [] begin_;
      begin_=newbegin;
      last_=begin_+sz;
      end_=begin_+new_capacity;
    }
  }
	
	template<typename value_type>
  void Vector<value_type>::shrink_to_fit(){
    if(dbg||vcall)std::cout<<"V Shrk t fit"<<std::endl;
    if(capacity()>size()){
      pointer* newbegin = new pointer[size()];
      for(size_type i=0; i<size(); i++){
        newbegin[i]=begin_[i];
      }
      for(size_type i=size(); i<capacity(); i++){
        if(begin_[i]!=nullptr)delete begin_[i];
      }
      size_type sz = size();
      if(begin_!=nullptr)delete [] begin_;
      begin_=newbegin;
      last_=begin_+sz;
      end_=begin_+sz;
    }
  }
}  // namespace I2P2

