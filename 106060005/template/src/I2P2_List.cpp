#include "../header/I2P2_List.h"

#include <iostream>
extern bool dbg;
extern bool lcall;
namespace I2P2 {
  /* Your definition for the List class goes here */
	
  	//!!!
  	//constructors
	
	template<typename value_type>
  	List<value_type>::List(){
		if(dbg)std::cout<<"L Const"<<std::endl;
		this->head = new Node<value_type>(123);
		this->tail = new Node<value_type>(45);

		this->head->isHead=true;
		head->next=tail;
		head->prev=nullptr;

		this->tail->isTail=true;
		tail->next=nullptr;
		tail->prev=head;
		
		_size=0;
	}
	
	template<typename value_type>
  	List<value_type>::List(const List& rhs){
		if(dbg)std::cout<<"L Copy"<<std::endl;
  		this->head = new Node<value_type>(-1);
		this->tail = new Node<value_type>(-2);

		this->head->isHead=true;
		head->next=tail;
		head->prev=nullptr;

		this->tail->isTail=true;
		tail->next=nullptr;
		tail->prev=head;
		
		_size=0;
  		
  		for(const_iterator iter=rhs.begin(); iter!=rhs.end(); ++iter){
  			push_back(*iter);
		}
	}
	
	template<typename value_type>
  	List<value_type>& List<value_type>::operator=(const List<value_type>& rhs){
		if(dbg||lcall)std::cout<<"L Op="<<std::endl;
  		clear();
  		for(const_iterator iter=rhs.begin(); iter!=rhs.end(); ++iter){
  			push_back(*iter);
		}
		return *this;
	}

	//destructor
	template<typename value_type>
  	List<value_type>::~List(){
		if(dbg||lcall)std::cout<<"L Des"<<std::endl;
  		clear();
		delete head;
  		delete tail;
	}
	
	template<typename value_type>
  	iterator<value_type> List<value_type>::begin(){
		if(dbg)std::cout<<"L itBegin"<<std::endl;
  		list_iterator<value_type> it(head->next);
		return (iterator(&it));
	}
	
	template<typename value_type>
  	const_iterator<value_type> List<value_type>::begin() const{
		if(dbg)std::cout<<"L cstit Begin"<<std::endl;
  		list_iterator<value_type> it(head->next);
		return (const_iterator(&it));
	}

	template<typename value_type>
  	iterator<value_type> List<value_type>::end(){
		if(dbg)std::cout<<"L it End"<<std::endl;
  		list_iterator<value_type> it(tail);
		return (iterator(&it));
	}
	
	template<typename value_type>
  	const_iterator<value_type> List<value_type>::end() const{
		if(dbg)std::cout<<"L cstit End"<<std::endl;
  		list_iterator<value_type> it(tail);
		return (const_iterator(&it));
	}
	
	template<typename value_type>
  	value_type& List<value_type>::front(){
		if(dbg||lcall)std::cout<<"L Front"<<std::endl;
  		return head->next->data;
	}
	
	template<typename value_type>
  	const value_type& List<value_type>::front() const{
		if(dbg||lcall)std::cout<<"L Front"<<std::endl;
  		return head->next->data;
	}
	
	template<typename value_type>
  	value_type& List<value_type>::back(){
		if(dbg||lcall)std::cout<<"L Back"<<std::endl;
  		return tail->prev->data;
	}
	
	template<typename value_type>
  	const value_type& List<value_type>::back() const{
		if(dbg||lcall)std::cout<<"L Back"<<std::endl;
  		return tail->prev->data;
	}
	
	template<typename value_type>
  	size_type List<value_type>::size() const{
		if(dbg)std::cout<<"L Sz"<<std::endl;
  		return _size;
	}
	
	template<typename value_type>
  	void List<value_type>::clear(){
		if(dbg||lcall)std::cout<<"L Clr"<<std::endl;
		Node<value_type>* nodeiter = head->next;
  		while(nodeiter!=tail){
			Node<value_type>* nxt = nodeiter->next;
			delete nodeiter;
			nodeiter = nxt;
		}
		this->head->isHead=true;
		head->prev=nullptr;
		head->next=tail;

		this->tail->isTail=true;
		tail->next=nullptr;
		tail->prev=head;
		_size=0;
	}
	
	template<typename value_type>
  	bool List<value_type>::empty() const{
		if(dbg||lcall)std::cout<<"L Emty"<<std::endl;
  		return (_size==0); 
	}
	
	template<typename value_type>
  	void List<value_type>::erase(const_iterator pos){
		if(dbg||lcall)std::cout<<"L Erase"<<std::endl;
  		Node<value_type>* tgt=pos.getNode();
		if(tgt!=head && tgt!=tail){
			(tgt->prev)->next=tgt->next;
  			(tgt->next)->prev=tgt->prev;
  			delete tgt;
  		
  			_size--;
		}
  		
	}
	
	template<typename value_type>
  	void List<value_type>::erase(const_iterator begin, const_iterator end){
		if(dbg||lcall)std::cout<<"L Erase range"<<std::endl;
		Node<value_type>* st = begin.getNode();
		Node<value_type>* ed = end.getNode();
		
		while(st!=ed){
			if(st!=head && st!=tail){
				(st->prev)->next=st->next;
				(st->next)->prev=st->prev;
				Node<value_type>* nxt=st->next;
				delete st;
				st=nxt;
				_size--;
			}
		}
	}
	
	template<typename value_type>
  	void List<value_type>::insert(const_iterator pos, size_type count, const_reference val){
		if(dbg||lcall)std::cout<<"L Insert"<<std::endl;
  		Node<value_type>* tgt = pos.getNode();
  		while(count--){
			Node<value_type>* newNode = new Node<value_type>(val);
			newNode->prev=tgt->prev;
			(tgt->prev)->next=newNode;
			newNode->next=tgt;
			tgt->prev=newNode;
			_size++;
		}
	}
	
	template<typename value_type>
  	void List<value_type>::insert(const_iterator pos, 
	  	const_iterator begin, const_iterator end){
		//std::cout<<"!!!!!!"<<std::endl;//!!!
		while(begin!=end){
			//std::cout<<*begin<<"! ";
			this->insert(pos, 1, *begin);
			begin++;
		}
		//std::cout<<std::endl;
		/*if(dbg||lcall)std::cout<<"L Insert range"<<std::endl;
  		Node* st = begin.getNode();
  		Node* ed = end.getNode();
		while(st!=ed){
			std::cout<<"? "<<std::endl;
			std::cout<<st->data<<"!"<<std::endl;
			//list_iterator li = list_iterator(pos.getNode());
			insert(pos, 1, st->data);
			st=st->next;
		}
		std::cout<<std::endl;//!!!
		//???*/
	}
	
	template<typename value_type>
  	void List<value_type>::pop_back(){
		if(dbg||lcall)std::cout<<"L Pop back"<<std::endl;
  		Node<value_type>* tgt = tail->prev;
  		if(tgt!=head){
  			(tgt->prev)->next=tgt->next;
			(tgt->next)->prev=tgt->prev;
			delete tgt;
			
			_size--;
		}
	}
	
	template<typename value_type>
  	void List<value_type>::pop_front(){
		if(dbg||lcall)std::cout<<"L Pop front"<<std::endl;
  		Node<value_type>* tgt = head->next;
  		if(tgt!=tail){
  			(tgt->prev)->next=tgt->next;
			(tgt->next)->prev=tgt->prev;
			delete tgt;
			
			_size--;	
		}
	}
	
	template<typename value_type>
  	void List<value_type>::push_back(const_reference val){
		if(dbg||lcall)std::cout<<"L Push back"<<std::endl;
  		Node<value_type>* newNode = new Node<value_type>(val);
  		newNode->prev=tail->prev;
  		(tail->prev)->next=newNode;
  		newNode->next=tail;
  		tail->prev=newNode;
  		
  		_size++;
	}
	
	template<typename value_type>
  	void List<value_type>::push_front(const_reference val){
		if(dbg||lcall)std::cout<<"L Push front"<<std::endl;
  		Node<value_type>* newNode = new Node<value_type>(val);
  		newNode->next=head->next;
  		(head->next)->prev=newNode;
  		newNode->prev=head;
  		head->next=newNode;
  		
  		_size++;
	}
}  // namespace I2P2
