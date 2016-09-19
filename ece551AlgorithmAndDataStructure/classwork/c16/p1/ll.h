#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>
template<typename T>
class Node{
			public:
				T data;
				Node* next;
				Node* previous;
				Node():next(NULL),previous(NULL){}
				Node(const T &d):data(d),next(NULL),previous(NULL){}
				Node(const T &d, Node<T> *n):data(d),next(n),previous(NULL){}
				Node(const T &d, Node<T> *n, Node<T> *p):data(d),next(n),previous(p){}
};

template<typename T>
class LinkedList{
	private:
		Node<T>* head;
		Node<T>* tail;
		int size;
	public:
		LinkedList():head(NULL),tail(NULL),size(0){}
		LinkedList(const LinkedList<T> & input){
			size=0;
			head=NULL;
			tail=NULL;
			Node<T>* input_current=input.head;
			while(input_current!=NULL){
				addBack(input_current->data);
				input_current=input_current->next;
			}
		}
				
				
		~LinkedList(){
			destroy();
		}
		void destroy(){
			if(size==0)
				return;
			else if(size==1){
				delete head;
			}
			else{
				Node<T>* current_delete=head;
				Node<T>* next_delete=head->next;
				while(current_delete!=NULL){
					delete current_delete;
					current_delete=next_delete;
					if(next_delete!=NULL)
						next_delete=next_delete->next;
				}
			}
			size=0;
			head=NULL;
			tail=NULL;	
		}
		 
		LinkedList<T>& operator=(LinkedList<T> &input){
			if(this!=&input){
				destroy();
				Node<T>* input_current=input.head;
				while(input_current!=NULL){
					addBack(input_current->data);
					input_current=input_current->next;
				}
			}
			return *this;	
		}
			
		void addFront(const T &item){
			Node<T>* Front_add=new Node<T>(item,head);
			if(head!=NULL)
				head->previous=Front_add;
			head=Front_add;
			if(size==0)
				tail=Front_add;
			size++;
		}
			
		void addBack(const T &item){
			Node<T>* Back_add=new Node<T>(item,NULL,tail);
			if(tail!=NULL)
				tail->next=Back_add;
			tail=Back_add;
			if(size==0)
				head=Back_add;
			size++;
		}

		bool remove(const T &item){
			Node<T>* current=head;
			if(size==0){
				return false;
			}
			
			while(current!=NULL){
				if(current->data==item){
					if(size==1){
						head=NULL;
						tail=NULL;
						delete current;
						size--;
						return true;
					}
					else if(current==head){
						head=current->next;
						current->next->previous=NULL;
						delete current;
						size--;
						return true;
					}
					else if(current==tail){
						tail=current->previous;
						current->previous->next=NULL;
						delete current;
						size--;
						return true;
					}
					else{	
						current->previous->next=current->next;
						current->next->previous=current->previous;
						delete current;
						size--;
						return true;
					}
				}
				else
					current=current->next;
			}
			return false;
		}
	
		T& operator[](int index) const{
			Node<T>* current=head;
			if((index>=size)||(index<0)){
				throw std::exception();
			}
			else{
				for(int i=0;i<index;i++){
					current=current->next;
				}
				return current->data;
			}
		}

		T& operator[](int index){
			Node<T>* current=head;
			if((index>=size)||(index<0)){
				throw std::exception();
			}
			else{
				for(int i=0;i<index;i++){
					current=current->next;
				}
				return current->data;
			}
		}

		int find(const T &item) const{
			int index=0;
			Node<T>* current=head;
			if(size==0)
				return -1;

			while(current!=NULL){
				if(current->data==item)
					return index;
				current=current->next;
				index++;
			}
			return -1;
		}

			
		int getSize() const{
			return size;
		}
};		
	
#endif
