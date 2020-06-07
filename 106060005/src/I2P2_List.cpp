#include "../header/I2P2_List.h"

#include <iostream>
extern bool dbg;
extern bool lcall;
namespace I2P2 {
  /* Your definition for the List class goes here */
	
  	//!!!
  	//constructors
  	List::List(){
		if(dbg)std::cout<<"L Const"<<std::endl;
		this->head = new Node(123);
		this->tail = new Node(45);

		this->head->isHead=true;
		head->next=tail;
		head->prev=nullptr;

		this->tail->isTail=true;
		tail->next=nullptr;
		tail->prev=head;
		
		_size=0;
	}
  	List::List(const List& rhs){
		if(dbg)std::cout<<"L Copy"<<std::endl;
  		this->head = new Node(-1);
		this->tail = new Node(-2);

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
  	List& List::operator=(const List& rhs){
		if(dbg||lcall)std::cout<<"L Op="<<std::endl;
  		clear();
  		for(const_iterator iter=rhs.begin(); iter!=rhs.end(); ++iter){
  			push_back(*iter);
		}
		return *this;
	}
	//destructor
  	List::~List(){
		if(dbg||lcall)std::cout<<"L Des"<<std::endl;
  		clear();
		delete head;
  		delete tail;
	}
  	
  	
  	iterator List::begin(){
		if(dbg)std::cout<<"L itBegin"<<std::endl;
  		list_iterator it(head->next);
		return (iterator(&it));
	}
  	const_iterator List::begin() const{
		if(dbg)std::cout<<"L cstit Begin"<<std::endl;
  		list_iterator it(head->next);
		return (const_iterator(&it));
	}
  	iterator List::end(){
		if(dbg)std::cout<<"L it End"<<std::endl;
  		list_iterator it(tail);
		return (iterator(&it));
	}
  	const_iterator List::end() const{
		if(dbg)std::cout<<"L cstit End"<<std::endl;
  		list_iterator it(tail);
		return (const_iterator(&it));
	}
  	reference List::front(){
		if(dbg||lcall)std::cout<<"L Front"<<std::endl;
  		return head->next->data;
	}
  	const_reference List::front() const{
		if(dbg||lcall)std::cout<<"L Front"<<std::endl;
  		return head->next->data;
	}
  	reference List::back(){
		if(dbg||lcall)std::cout<<"L Back"<<std::endl;
  		return tail->prev->data;
	}
  	const_reference List::back() const{
		if(dbg||lcall)std::cout<<"L Back"<<std::endl;
  		return tail->prev->data;
	}
  	size_type List::size() const{
		if(dbg)std::cout<<"L Sz"<<std::endl;
  		return _size;
	}
  	void List::clear(){
		if(dbg||lcall)std::cout<<"L Clr"<<std::endl;
		Node* nodeiter = head->next;
  		while(nodeiter!=tail){
			Node* nxt = nodeiter->next;
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
  	bool List::empty() const{
		if(dbg||lcall)std::cout<<"L Emty"<<std::endl;
  		return (_size==0);
	}
  	void List::erase(const_iterator pos){
		if(dbg||lcall)std::cout<<"L Erase"<<std::endl;
  		Node* tgt=pos.getNode();
		if(tgt!=head && tgt!=tail){
			(tgt->prev)->next=tgt->next;
  			(tgt->next)->prev=tgt->prev;
  			delete tgt;
  		
  			_size--;
		}
  		
	}
  	void List::erase(const_iterator begin, const_iterator end){
		if(dbg||lcall)std::cout<<"L Erase range"<<std::endl;
		Node* st = begin.getNode();
		Node* ed = end.getNode();
		
		while(st!=ed){
			if(st!=head && st!=tail){
				(st->prev)->next=st->next;
				(st->next)->prev=st->prev;
				Node* nxt=st->next;
				delete st;
				st=nxt;
				_size--;
			}
		}
	}
  	void List::insert(const_iterator pos, size_type count, const_reference val){
		if(dbg||lcall)std::cout<<"L Insert"<<std::endl;
  		Node* tgt = pos.getNode();
  		while(count--){
			Node* newNode = new Node(val);
			newNode->prev=tgt->prev;
			(tgt->prev)->next=newNode;
			newNode->next=tgt;
			tgt->prev=newNode;
			_size++;
		}
	}
  	void List::insert(const_iterator pos, const_iterator begin, const_iterator end){
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
  	void List::pop_back(){
		if(dbg||lcall)std::cout<<"L Pop back"<<std::endl;
  		Node* tgt = tail->prev;
  		if(tgt!=head){
  			(tgt->prev)->next=tgt->next;
			(tgt->next)->prev=tgt->prev;
			delete tgt;
			
			_size--;
		}
	}
  	void List::pop_front(){
		if(dbg||lcall)std::cout<<"L Pop front"<<std::endl;
  		Node* tgt = head->next;
  		if(tgt!=tail){
  			(tgt->prev)->next=tgt->next;
			(tgt->next)->prev=tgt->prev;
			delete tgt;
			
			_size--;	
		}
	}
  	void List::push_back(const_reference val){
		if(dbg||lcall)std::cout<<"L Push back"<<std::endl;
  		Node* newNode = new Node(val);
  		newNode->prev=tail->prev;
  		(tail->prev)->next=newNode;
  		newNode->next=tail;
  		tail->prev=newNode;
  		
  		_size++;
	}
  	void List::push_front(const_reference val){
		if(dbg||lcall)std::cout<<"L Push front"<<std::endl;
  		Node* newNode = new Node(val);
  		newNode->next=head->next;
  		(head->next)->prev=newNode;
  		newNode->prev=head;
  		head->next=newNode;
  		
  		_size++;
	}
}  // namespace I2P2
