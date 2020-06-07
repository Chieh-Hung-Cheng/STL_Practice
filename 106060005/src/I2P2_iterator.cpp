#include "../header/I2P2_iterator.h"

#include <iostream>
bool dbg=false;
bool vcall=false;
bool lcall=false;

namespace I2P2 {
	//!!!
	//vector iterator
	//!!!
	vector_iterator::vector_iterator(){
		this->ptrofptr=nullptr;
		this->idx = 0;
	}
  	vector_iterator::vector_iterator(pointer* ptrofptr, size_type idx){
		this->ptrofptr=ptrofptr;
		this->idx = idx;
	}
  	iterator_impl_base& vector_iterator::operator++(){
		ptrofptr++;
		idx++;
		return *this;
	}
  	iterator_impl_base& vector_iterator::operator--(){
		ptrofptr--;
		idx--;
		return *this;
	}
  	iterator_impl_base& vector_iterator::operator+=(difference_type offset){
		ptrofptr=ptrofptr+offset;
		idx=idx+offset;
	}
  	iterator_impl_base& vector_iterator::operator-=(difference_type offset){
		ptrofptr=ptrofptr-offset;
		idx=idx-offset;
	}
  	bool vector_iterator::operator==(const iterator_impl_base &rhs) const{
		//return ((this->getPtrofPtr())==(rhs.getPtrofPtr()));//*
		return (this->getIdx() == rhs.getIdx());
	}
  	bool vector_iterator::operator!=(const iterator_impl_base &rhs) const{
		//return ((this->getPtrofPtr())!=(rhs.getPtrofPtr()));//*
		return (this->getIdx() != rhs.getIdx());
	}
	//???
  	bool vector_iterator::operator<(const iterator_impl_base &rhs) const{
		return ((this->getPtrofPtr())<(rhs.getPtrofPtr()));
	}
  	bool vector_iterator::operator>(const iterator_impl_base &rhs) const{
		return ((this->getPtrofPtr())>(rhs.getPtrofPtr()));
	}
  	bool vector_iterator::operator<=(const iterator_impl_base &rhs) const{
		return ((this->getPtrofPtr())<=(rhs.getPtrofPtr()));
	}
  	bool vector_iterator::operator>=(const iterator_impl_base &rhs) const{
		return ((this->getPtrofPtr())>=(rhs.getPtrofPtr()));
	}
  	difference_type vector_iterator::operator-(const iterator_impl_base &rhs) const{
		return ((this->getPtrofPtr())-(rhs.getPtrofPtr()));
	}
  	pointer vector_iterator::operator->() const{
		return *(this->ptrofptr);	  
	}
  	reference vector_iterator::operator*() const{
		return *(*(this->ptrofptr));
	}
  	reference vector_iterator::operator[](difference_type offset) const{
		return *(*(this->ptrofptr+offset));//error here
	}


	//!!!
	//list iterator
	//!!!
	list_iterator::list_iterator(){
		node=nullptr;
	}
	list_iterator::list_iterator(Node* node){
		this->node = node;
	}
	iterator_impl_base& list_iterator::operator++(){
  		node = node->next;
		return *this;
	}
	iterator_impl_base& list_iterator::operator--(){
  		node = node->prev;
  		return *this;
	}
	iterator_impl_base& list_iterator::operator+=(difference_type offset){
  		while(offset--){
  			node=node->next;	
		}
		return *this;
	}
	iterator_impl_base& list_iterator::operator-=(difference_type offset){
  		while(offset--){
  			node=node->prev;
		}
		return *this;
	}
	bool list_iterator::operator==(const iterator_impl_base &rhs) const{
		size_type mypos = getPos(this->node);
		size_type rhspos = getPos(rhs.getNode());
  		return (mypos==rhspos);
	}
	bool list_iterator::operator!=(const iterator_impl_base &rhs) const{
		size_type mypos = getPos(this->node);
		size_type rhspos = getPos(rhs.getNode());
  		return (mypos!=rhspos);
	}
	bool list_iterator::operator<(const iterator_impl_base &rhs) const{
		size_type mypos = getPos(this->node);
		size_type rhspos = getPos(rhs.getNode());
  		return (mypos<rhspos);
	}
	bool list_iterator::operator>(const iterator_impl_base &rhs) const{
		size_type mypos = getPos(this->node);
		size_type rhspos = getPos(rhs.getNode());
  		return (mypos>rhspos);
	}
	bool list_iterator::operator<=(const iterator_impl_base &rhs) const{
		size_type mypos = getPos(this->node);
		size_type rhspos = getPos(rhs.getNode());
  		return (mypos<=rhspos);
	}
	bool list_iterator::operator>=(const iterator_impl_base &rhs) const{
		size_type mypos = getPos(this->node);
		size_type rhspos = getPos(rhs.getNode());
  		return (mypos>=rhspos);
	}
	difference_type list_iterator::operator-(const iterator_impl_base &rhs) const{
		size_type mypos = getPos(this->node);
		size_type rhspos = getPos(rhs.getNode());
  		return (mypos-rhspos);
	}
	pointer list_iterator::operator->() const{
		return &(this->node->data);//???
	}
	reference list_iterator::operator*() const{
		return node->data;
	}
	reference list_iterator::operator[](difference_type offset) const{
		if(dbg)std::cout<<"[]"<<std::endl;
		Node* target=this->node;
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
	const_iterator::~const_iterator(){
		if(dbg)std::cout<<"cstit destruct"<<std::endl;
		if(p_!=nullptr) delete p_;
	}
	const_iterator::const_iterator(){
		if(dbg)std::cout<<"cstit const"<<std::endl;
		p_=nullptr;
	}
	const_iterator::const_iterator(const const_iterator& rhs){
		if(dbg)std::cout<<"cstit cpy const by cstit"<<std::endl;
		p_=rhs.p_->clone();
	}
	const_iterator::const_iterator(iterator_impl_base* p){
		if(dbg)std::cout<<"cstit cpy const by itbase"<<std::endl;
		p_=p->clone();
	}
	const_iterator& const_iterator::operator=(const const_iterator &rhs){
		if(dbg)std::cout<<"cstit op="<<std::endl;
		this->p_ = rhs.p_->clone();
		return *this;
	} 
	const_iterator& const_iterator::operator++(){
		if(dbg)std::cout<<"++cstit"<<std::endl;
		++ *(p_);
		return *this;
	}
	const_iterator const_iterator::operator++(int){//???
		if(dbg)std::cout<<"cstit++"<<std::endl;
		const_iterator cstit(p_);
		++ *this;
		return cstit;
	}
	const_iterator& const_iterator::operator--(){
		if(dbg)std::cout<<"--cstit"<<std::endl;
		-- *(p_);
		return *this;
	}
	const_iterator const_iterator::operator--(int){//???
		if(dbg)std::cout<<"cstit--"<<std::endl;
		const_iterator cstit(p_);
		-- *this;
		return cstit;
	}
	const_iterator& const_iterator::operator+=(difference_type offset){
		if(dbg)std::cout<<"cstit+="<<std::endl;
		while(offset--){
			++ (*this);
		}
		return *this;
	}
	const_iterator const_iterator::operator+(difference_type offset) const{
		if(dbg)std::cout<<"cstit+"<<std::endl;
		const_iterator cstit(p_);
		while(offset--){
			++cstit;
		}
		return cstit;
	}
	const_iterator& const_iterator::operator-=(difference_type offset){
		if(dbg)std::cout<<"cstit-="<<std::endl;
		while(offset--){
			-- *(this);
		}
		return *this;
	} 
	const_iterator const_iterator::operator-(difference_type offset) const{
		if(dbg)std::cout<<"cstit-offset"<<std::endl;
		const_iterator cstit(p_);
		while(offset--){
			--cstit;
		}
		return cstit;
	}
	difference_type const_iterator::operator-(const const_iterator &rhs) const{
		if(dbg)std::cout<<"cstit-rhs"<<std::endl;
		return *(this->p_) - *(rhs.p_);
	}
	const_pointer const_iterator::operator->() const{//type changed to const?
		if(dbg)std::cout<<"cstit->"<<std::endl;
		return &(*(*p_));
	}
	const_reference const_iterator::operator*() const{//type changed to const?
		if(dbg)std::cout<<"*cstit"<<std::endl;
		return *(*(p_));
	}
	const_reference const_iterator::operator[](difference_type offset) const{//type changed to const?
		if(dbg)std::cout<<"cstit[]"<<std::endl;
		return p_->operator[](offset);
	}
	bool const_iterator::operator==(const const_iterator &rhs) const{
		if(dbg)std::cout<<"cstit=="<<std::endl;
		return *(this->p_) == *(rhs.p_);
	}
	bool const_iterator::operator!=(const const_iterator &rhs) const{
		if(dbg)std::cout<<"cstit!="<<std::endl;
		return *(this->p_) != *(rhs.p_);
	}
	bool const_iterator::operator<(const const_iterator &rhs) const{
		if(dbg)std::cout<<"<"<<std::endl;
		return *(this->p_) < *(rhs.p_);
	}
	bool const_iterator::operator>(const const_iterator &rhs) const{
		if(dbg)std::cout<<">"<<std::endl;
		return *(this->p_) > *(rhs.p_);
	}
	bool const_iterator::operator<=(const const_iterator &rhs) const{
		if(dbg)std::cout<<"<="<<std::endl;
		return *(this->p_) <= *(rhs.p_);
	}
	bool const_iterator::operator>=(const const_iterator &rhs) const{
		if(dbg)std::cout<<">="<<std::endl;
		return *(this->p_) >= *(rhs.p_);
	}
	
	//!!!
	//iterator
	//!!
	iterator::iterator(){
		if(dbg)std::cout<<"it const"<<std::endl;
		p_=nullptr;
	}
	iterator::iterator(iterator_impl_base *p){
		if(dbg)std::cout<<"it const by itbase"<<std::endl;
		p_=p->clone();
	}
	iterator::iterator(const iterator &rhs){
		if(dbg)std::cout<<"it const by it"<<std::endl;
		p_=rhs.p_->clone();
	}
	iterator& iterator::operator++(){
		if(dbg)std::cout<<"++it"<<std::endl;
		++(*p_);
		return *this;
	}
	iterator iterator::operator++(int){
		if(dbg)std::cout<<"it++"<<std::endl;
		iterator it(p_);
		++ *this;
		return it;
	}
	iterator& iterator::operator--(){
		if(dbg)std::cout<<"--it"<<std::endl;
		--(*p_);
		return *this;
	}
	iterator iterator::operator--(int){
		if(dbg)std::cout<<"it--"<<std::endl;
		iterator it(p_);
		-- *this;
		return it;
	}
	iterator& iterator::operator+=(difference_type offset){
		if(dbg)std::cout<<"it+="<<std::endl;
		while(offset--){
			++(*this);
		}
		return *this;
	}
	iterator iterator::operator+(difference_type offset) const{
		if(dbg)std::cout<<"it+"<<std::endl;
		iterator it(p_);
		while(offset--){
			++it;
		}
		return it;
	}
	iterator& iterator::operator-=(difference_type offset){
		if(dbg)std::cout<<"it-="<<std::endl;
		while(offset--){
			--(*this);
		}
		return *this;
	}
	iterator iterator::operator-(difference_type offset) const{
		if(dbg)std::cout<<"it-offset"<<std::endl;
		iterator it(p_);
		while(offset--){
			--it;
		}
		return it;
	}
	difference_type iterator::operator-(const iterator &rhs) const{
		if(dbg)std::cout<<"it-rhs"<<std::endl;
		return *(this->p_) - *(rhs.p_);
	}
	pointer iterator::operator->() const{
		if(dbg)std::cout<<"it->"<<std::endl;
		return &(*(*p_));
	}
	reference iterator::operator*() const{
		if(dbg)std::cout<<"*it"<<std::endl;
		return *(*p_);
	}
	reference iterator::operator[](difference_type offset) const{
		if(dbg)std::cout<<"it[]"<<std::endl;
		return p_->operator[](offset);
	}
	
  	
}

