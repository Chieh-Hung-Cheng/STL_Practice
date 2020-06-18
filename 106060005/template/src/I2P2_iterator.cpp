#include "../header/I2P2_iterator.h"

#include <iostream>
bool dbg=false;
bool vcall=false;
bool lcall=false;

namespace I2P2 {
	//!!!
	//vector iterator
	//!!!
	template<typename value_type>
	vector_iterator<value_type>::vector_iterator(){
		this->ptrofptr=nullptr;
		this->idx = 0;
	}

	template<typename value_type>
  	vector_iterator<value_type>::vector_iterator(pointer* ptrofptr, size_type idx){
		this->ptrofptr=ptrofptr;
		this->idx = idx;
	}

	template<typename value_type>
  	iterator_impl_base<value_type>& vector_iterator<value_type>::operator++(){
		ptrofptr++;
		idx++;
		return *this;
	}
	
	template<typename value_type>
  	iterator_impl_base<value_type>& vector_iterator<value_type>::operator--(){
		ptrofptr--;
		idx--;
		return *this;
	}
	
	template<typename value_type>
  	iterator_impl_base<value_type>& vector_iterator<value_type>::operator+=(difference_type offset){
		ptrofptr=ptrofptr+offset;
		idx=idx+offset;
	}
	
	template<typename value_type>
  	iterator_impl_base<value_type>& vector_iterator<value_type>::operator-=(difference_type offset){
		ptrofptr=ptrofptr-offset;
		idx=idx-offset;
	}
	
	template<typename value_type>
  	bool vector_iterator<value_type>::operator==(const iterator_impl_base<value_type>& rhs) const{
		//return ((this->getPtrofPtr())==(rhs.getPtrofPtr()));//*
		return (this->getIdx() == rhs.getIdx());
	}
	
	template<typename value_type>
  	bool vector_iterator<value_type>::operator!=(const iterator_impl_base<value_type>& rhs) const{
		//return ((this->getPtrofPtr())!=(rhs.getPtrofPtr()));//*
		return (this->getIdx() != rhs.getIdx());
	}
	
	template<typename value_type>
  	bool vector_iterator<value_type>::operator<(const iterator_impl_base<value_type>& rhs) const{
		return ((this->getPtrofPtr())<(rhs.getPtrofPtr()));
	}
	
	template<typename value_type>
  	bool vector_iterator<value_type>::operator>(const iterator_impl_base<value_type>& rhs) const{
		return ((this->getPtrofPtr())>(rhs.getPtrofPtr()));
	}
	
	template<typename value_type>
  	bool vector_iterator<value_type>::operator<=(const iterator_impl_base<value_type>& rhs) const{
		return ((this->getPtrofPtr())<=(rhs.getPtrofPtr()));
	}
	
	template<typename value_type>
  	bool vector_iterator<value_type>::operator>=(const iterator_impl_base<value_type> &rhs) const{
		return ((this->getPtrofPtr())>=(rhs.getPtrofPtr()));
	}
	
	template<typename value_type>
  	difference_type vector_iterator<value_type>::operator-(const iterator_impl_base<value_type> &rhs) const{
		return ((this->getPtrofPtr())-(rhs.getPtrofPtr()));
	}
	
	template<typename value_type>
  	value_type* vector_iterator<value_type>::operator->() const{
		return *(this->ptrofptr);	  
	}
	
	template<typename value_type>
  	value_type& vector_iterator<value_type>::operator*() const{
		return *(*(this->ptrofptr));
	}
	
	template<typename value_type>
  	value_type& vector_iterator<value_type>::operator[](difference_type offset) const{
		return *(*(this->ptrofptr+offset));//error here
	}


	//!!!
	//list iterator
	//!!!
	
	template<typename value_type>
	list_iterator<value_type>::list_iterator(){
		node=nullptr;
	}
	
	template<typename value_type>
	list_iterator<value_type>::list_iterator(Node<value_type>* node){
		this->node = node;
	}
	
	template<typename value_type>
	iterator_impl_base<value_type>& list_iterator<value_type>::operator++(){
  		node = node->next;
		return *this;
	}
	
	template<typename value_type>
	iterator_impl_base<value_type>& list_iterator<value_type>::operator--(){
  		node = node->prev;
  		return *this;
	}
	
	template<typename value_type>
	iterator_impl_base<value_type>& list_iterator<value_type>::operator+=(difference_type offset){
  		while(offset--){
  			node=node->next;	
		}
		return *this;
	}
	
	template<typename value_type>
	iterator_impl_base<value_type>& list_iterator<value_type>::operator-=(difference_type offset){
  		while(offset--){
  			node=node->prev;
		}
		return *this;
	}
	
	template<typename value_type>
	bool list_iterator<value_type>::operator==(const iterator_impl_base<value_type> &rhs) const{
		size_type mypos = getPos(this->node);
		size_type rhspos = getPos(rhs.getNode());
  		return (mypos==rhspos);
	}
	
	template<typename value_type>
	bool list_iterator<value_type>::operator!=(const iterator_impl_base<value_type> &rhs) const{
		size_type mypos = getPos(this->node);
		size_type rhspos = getPos(rhs.getNode());
  		return (mypos!=rhspos);
	}
	
	template<typename value_type>
	bool list_iterator<value_type>::operator<(const iterator_impl_base<value_type> &rhs) const{
		size_type mypos = getPos(this->node);
		size_type rhspos = getPos(rhs.getNode());
  		return (mypos<rhspos);
	}
	
	template<typename value_type>
	bool list_iterator<value_type>::operator>(const iterator_impl_base<value_type> &rhs) const{
		size_type mypos = getPos(this->node);
		size_type rhspos = getPos(rhs.getNode());
  		return (mypos>rhspos);
	}
	
	template<typename value_type>
	bool list_iterator<value_type>::operator<=(const iterator_impl_base<value_type> &rhs) const{
		size_type mypos = getPos(this->node);
		size_type rhspos = getPos(rhs.getNode());
  		return (mypos<=rhspos);
	}
	
	template<typename value_type>
	bool list_iterator<value_type>::operator>=(const iterator_impl_base<value_type> &rhs) const{
		size_type mypos = getPos(this->node);
		size_type rhspos = getPos(rhs.getNode());
  		return (mypos>=rhspos);
	}
	
	template<typename value_type>
	difference_type list_iterator<value_type>::operator-(const iterator_impl_base<value_type> &rhs) const{
		size_type mypos = getPos(this->node);
		size_type rhspos = getPos(rhs.getNode());
  		return (mypos-rhspos);
	}
	
	template<typename value_type>
	value_type* list_iterator<value_type>::operator->() const{
		return &(this->node->data);//???
	}
	
	template<typename value_type>
	value_type& list_iterator<value_type>::operator*() const{
		return node->data;
	}
	
	template<typename value_type>
	value_type& list_iterator<value_type>::operator[](difference_type offset) const{
		if(dbg)std::cout<<"[]"<<std::endl;
		Node<value_type>* target=this->node;
		if(offset>=0){
			while(offset--){
				target=target->next;
			}
			return target->data;
		}
		else if(offset<0){
			offset=-offset;
			while(offset--){
				target=target->prev;
			}
			return target->data;
		}
		
	}

	
	//!!!
	//const iterator
	//!!!
	
	template<typename value_type>
	const_iterator<value_type>::~const_iterator(){
		if(dbg)std::cout<<"cstit destruct"<<std::endl;
		if(p_!=nullptr) delete p_;
	}
	
	template<typename value_type>
	const_iterator<value_type>::const_iterator(){
		if(dbg)std::cout<<"cstit const"<<std::endl;
		p_=nullptr;
	}
	
	template<typename value_type>
	const_iterator<value_type>::const_iterator(const const_iterator& rhs){
		if(dbg)std::cout<<"cstit cpy const by cstit"<<std::endl;
		p_=rhs.p_->clone();
	}
	
	template<typename value_type>
	const_iterator<value_type>::const_iterator(iterator_impl_base<value_type>* p){
		if(dbg)std::cout<<"cstit cpy const by itbase"<<std::endl;
		p_=p->clone();
	}
	
	template<typename value_type>
	const_iterator<value_type>& const_iterator<value_type>::operator=(const const_iterator<value_type> &rhs){
		if(dbg)std::cout<<"cstit op="<<std::endl;
		this->p_ = rhs.p_->clone();
	} 
	
	template<typename value_type>
	const_iterator<value_type>& const_iterator<value_type>::operator++(){
		if(dbg)std::cout<<"++cstit"<<std::endl;
		++ *(p_);
		return *this;
	}
	
	template<typename value_type>
	const_iterator<value_type> const_iterator<value_type>::operator++(int){//???
		if(dbg)std::cout<<"cstit++"<<std::endl;
		const_iterator<value_type> cstit(p_);
		++ *this;
		return cstit;
	}
	
	template<typename value_type>
	const_iterator<value_type>& const_iterator<value_type>::operator--(){
		if(dbg)std::cout<<"--cstit"<<std::endl;
		-- *(p_);
		return *this;
	}
	
	template<typename value_type>
	const_iterator<value_type> const_iterator<value_type>::operator--(int){//???
		if(dbg)std::cout<<"cstit--"<<std::endl;
		const_iterator cstit(p_);
		-- *this;
		return cstit;
	}
	
	template<typename value_type>
	const_iterator<value_type>& const_iterator<value_type>::operator+=(difference_type offset){
		if(dbg)std::cout<<"cstit+="<<std::endl;
		while(offset--){
			++ (*this);
		}
		return *this;
	}
	
	template<typename value_type>
	const_iterator<value_type> const_iterator<value_type>::operator+(difference_type offset) const{
		if(dbg)std::cout<<"cstit+"<<std::endl;
		const_iterator cstit(p_);
		while(offset--){
			++cstit;
		}
		return cstit;
	}
	
	template<typename value_type>
	const_iterator<value_type>& const_iterator<value_type>::operator-=(difference_type offset){
		if(dbg)std::cout<<"cstit-="<<std::endl;
		while(offset--){
			-- *(this);
		}
		return *this;
	} 
	
	template<typename value_type>
	const_iterator<value_type> const_iterator<value_type>::operator-(difference_type offset) const{
		if(dbg)std::cout<<"cstit-offset"<<std::endl;
		const_iterator cstit(p_);
		while(offset--){
			--cstit;
		}
		return cstit;
	}
	
	template<typename value_type>
	difference_type const_iterator<value_type>::operator-(const const_iterator<value_type> &rhs) const{
		if(dbg)std::cout<<"cstit-rhs"<<std::endl;
		return *(this->p_) - *(rhs.p_);
	}
	
	template<typename value_type>
	value_type* const_iterator<value_type>::operator->() const{//type changed to const?
		if(dbg)std::cout<<"cstit->"<<std::endl;
		return &(*(*p_));
	}
	
	template<typename value_type>
	value_type& const_iterator<value_type>::operator*() const{//type changed to const?
		if(dbg)std::cout<<"*cstit"<<std::endl;
		return *(*(p_));
	}
	
	template<typename value_type>
	value_type& const_iterator<value_type>::operator[](difference_type offset) const{//type changed to const?
		if(dbg)std::cout<<"cstit[]"<<std::endl;
		return p_->operator[](offset);
	}
	
	template<typename value_type>
	bool const_iterator<value_type>::operator==(const const_iterator<value_type> &rhs) const{
		if(dbg)std::cout<<"cstit=="<<std::endl;
		return *(this->p_) == *(rhs.p_);
	}
	
	template<typename value_type>
	bool const_iterator<value_type>::operator!=(const const_iterator<value_type> &rhs) const{
		if(dbg)std::cout<<"cstit!="<<std::endl;
		return *(this->p_) != *(rhs.p_);
	}
	
	template<typename value_type>
	bool const_iterator<value_type>::operator<(const const_iterator<value_type> &rhs) const{
		if(dbg)std::cout<<"<"<<std::endl;
		return *(this->p_) < *(rhs.p_);
	}
	
	template<typename value_type>
	bool const_iterator<value_type>::operator>(const const_iterator<value_type> &rhs) const{
		if(dbg)std::cout<<">"<<std::endl;
		return *(this->p_) > *(rhs.p_);
	}
	
	template<typename value_type>
	bool const_iterator<value_type>::operator<=(const const_iterator<value_type> &rhs) const{
		if(dbg)std::cout<<"<="<<std::endl;
		return *(this->p_) <= *(rhs.p_);
	}
	
	template<typename value_type>
	bool const_iterator<value_type>::operator>=(const const_iterator<value_type> &rhs) const{
		if(dbg)std::cout<<">="<<std::endl;
		return *(this->p_) >= *(rhs.p_);
	}
	
	//!!!
	//iterator
	//!!
	
	template<typename value_type>
	iterator<value_type>::iterator(){
		if(dbg)std::cout<<"it const"<<std::endl;
		this->p_=nullptr;
	}
	
	template<typename value_type>
	iterator<value_type>::iterator(iterator_impl_base<value_type> *p){
		if(dbg)std::cout<<"it const by itbase"<<std::endl;
		this->p_=p->clone();
	}
	
	template<typename value_type>
	iterator<value_type>::iterator(const iterator<value_type> &rhs){
		if(dbg)std::cout<<"it const by it"<<std::endl;
		this->p_=rhs.p_->clone();
	}
	
	template<typename value_type>
	iterator<value_type>& iterator<value_type>::operator++(){
		if(dbg)std::cout<<"++it"<<std::endl;
		++(*(this->p_));
		return *this;
	}
	
	template<typename value_type>
	iterator<value_type> iterator<value_type>::operator++(int){
		if(dbg)std::cout<<"it++"<<std::endl;
		iterator<value_type> it(this->p_);
		++ *this;
		return it;
	}
	
	template<typename value_type>
	iterator<value_type>& iterator<value_type>::operator--(){
		if(dbg)std::cout<<"--it"<<std::endl;
		--(*(this->p_));
		return *this;
	}
	
	template<typename value_type>
	iterator<value_type> iterator<value_type>::operator--(int){
		if(dbg)std::cout<<"it--"<<std::endl;
		iterator it(this->p_);
		-- *this;
		return it;
	}
	
	template<typename value_type>
	iterator<value_type>& iterator<value_type>::operator+=(difference_type offset){
		if(dbg)std::cout<<"it+="<<std::endl;
		while(offset--){
			++(*this);
		}
		return *this;
	}
	
	template<typename value_type>
	iterator<value_type> iterator<value_type>::operator+(difference_type offset) const{
		if(dbg)std::cout<<"it+"<<std::endl;
		iterator<value_type> it(this->p_);
		while(offset--){
			++it;
		}
		return it;
	}
	
	template<typename value_type>
	iterator<value_type>& iterator<value_type>::operator-=(difference_type offset){
		if(dbg)std::cout<<"it-="<<std::endl;
		while(offset--){
			--(*this);
		}
		return *this;
	}
	
	template<typename value_type>
	iterator<value_type> iterator<value_type>::operator-(difference_type offset) const{
		if(dbg)std::cout<<"it-offset"<<std::endl;
		iterator<value_type> it(this->p_);
		while(offset--){
			--it;
		}
		return it;
	}
	
	template<typename value_type>
	difference_type iterator<value_type>::operator-(const iterator &rhs) const{
		if(dbg)std::cout<<"it-rhs"<<std::endl;
		return *(this->p_) - *(rhs.p_);
	}
	
	template<typename value_type>
	value_type* iterator<value_type>::operator->() const{
		if(dbg)std::cout<<"it->"<<std::endl;
		return &(*(*(this->p_)));
	}
	
	template<typename value_type>
	value_type& iterator<value_type>::operator*() const{
		if(dbg)std::cout<<"*it"<<std::endl;
		return *(*(this->p_));
	}
	
	template<typename value_type>
	value_type& iterator<value_type>::operator[](difference_type offset) const{
		if(dbg)std::cout<<"it[]"<<std::endl;
		return this->p_->operator[](offset);
	}
	
  	
}

