#include"set.h"
#include<iostream>
template<typename K>
class BstSet : public Set<K> 
{
	public:
		int size;
//////////////////////////////////////////////////////
		class Pair{
			public:
				K key;
			  Pair* left;
				Pair* right;
				Pair(const K & in_key, Pair* in_left, Pair* in_right):key(in_key),left(in_left),right(in_right){}
		};
//////////////////////////////////////////////////////
		Pair* root;
		BstSet():size(0),root(NULL){}
		~BstSet(){
			size=0;
			destroy(root);
		}
//////////////////////////////////////////////////////
		void destroy(Pair* current){
			if(current!=NULL){
				destroy(current->left);
				destroy(current->right);
				delete current;
			}
		}
//////////////////////////////////////////////////////
		void inorder(Pair* current){
			if(current!=NULL){
				inorder(current->left);
				std::cout<<current->key<<" ";
				inorder(current->right);
			}
		}
		void inorder_print(){
			inorder(root);
			std::cout<<std::endl;
		}
//////////////////////////////////////////////////////		
		void preorder(Pair* current){
			if(current!=NULL){
				std::cout<<current->key<<" ";
				preorder(current->left);
				preorder(current->right);
			}
		}
	virtual	void preorder_print(){
			preorder(root);
			std::cout<<std::endl;
		}

//////////////////////////////////////////////////////		
		void postorder(Pair* current){
			if(current!=NULL){
				postorder(current->left);
				postorder(current->right);
				std::cout<<current->key<<" ";
			}
		}
		void postorder_print(){
			postorder(root);
			std::cout<<std::endl;
		}

	
//////////////////////////////////////////////////////
		void add_helper(const K &key,Pair* current){
			if(key<current->key){
				if(current->left==NULL){
					current->left=new Pair(key,NULL,NULL);
					return;
				}
				else{
					add_helper(key,current->left);
					return;
				}
			}
			else if(key>current->key){
				if(current->right==NULL){
					current->right=new Pair(key,NULL,NULL);
					return;
				}
				else{
					add_helper(key,current->right);
					return;
				}
			}
		}
		void add(const K &key){
			if(root==NULL){
				root=new Pair(key,NULL,NULL);
				size++;
				return;
			}
			else{
				add_helper(key,root);
				size++;
				return;
			}
		}
//////////////////////////////////////////////////////////////
		bool lookup_helper(const K& key,const Pair* current) const{
			if(current==NULL){
				return false;
			}
			else if(current->key==key){
				return true;
			}
			else if(key<current->key){
				return lookup_helper(key,current->left);
			}
			else{
				return lookup_helper(key,current->right);
			}
		}
		bool contains(const K& key) const {
			return lookup_helper(key,root);
		}
//////////////////////////////////////////////////////////////
		Pair* remove_lookup_helper(const K& key,Pair* current, Pair* father) const{
			if(current==NULL){
				return NULL;
			}
			else if(current->key==key){
				return father;
			}
			else if(key<current->key){
				return remove_lookup_helper(key,current->left,current);
			}
			else{
				return remove_lookup_helper(key,current->right,current);
			}
		}
		Pair* remove_lookup(const K& key) const {
			return remove_lookup_helper(key,root,NULL);
		}
//////////////////////////////////////////////////////////////
		Pair* right_mostleft(Pair* current, Pair* father){
			if(current->left==NULL){
				father->right=current->right;
				return current;
			}
			else{
				while(current->left!=NULL){
					father=current;
					current=current->left;
				}
				father->left=current->right;
				return current;
			}
		}
		bool branch_check(Pair* father,const K& key){
			if(father->left==NULL)
				return false;
			else if(father->right==NULL)
				return true;
			else if(father->left->key==key)
				return true;
			else
				return false;
		}

		
		void remove(const K& key){
				Pair* father=remove_lookup(key);
				if(father==NULL){
					if(root->key!=key)
						return;
				}
				Pair* temp=NULL;
				Pair* current=NULL;
				size--;
				if(father==NULL){
					if(root->left==NULL){
						temp=root;
						root=root->right;
						delete temp;
					}
					else if(root->right==NULL){
						temp=root;
						root=root->left;
						delete temp;
					}
					else{
						temp=right_mostleft(root->right,root);
						temp->right=root->right;
						temp->left=root->left;
						delete root;
						root=temp;
					}
				}
				else{
					if(branch_check(father,key)){
						current=father->left;
						if(current->left==NULL){
							father->left=current->right;
							delete current;
						}
						else if(current->right==NULL){
							father->left=current->left;
							delete current;
						}
						else{
							father->left=right_mostleft(current,father);
							father->left->left=current->left;
							father->left->right=current->right;
							delete current;
						}
					}
					else{
						current=father->right;
						if(current->left==NULL){
							father->right=current->right;
							delete current;
						}
						else if(current->right==NULL){
							father->right=current->left;
							delete current;
						}
						else{
							father->right=right_mostleft(current,father);
							father->right->left=current->left;
							father->right->right=current->right;
							delete current;
						}
					}
				}
			}
};	
