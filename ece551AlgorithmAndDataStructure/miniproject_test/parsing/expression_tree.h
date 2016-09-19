#include<assert.h>
#include<stack>
#include<iostream>
#include<vector>
using namespace std;
class Nodes{
//==============
//field defination
//=============
	public:
		float num;//store number
		char op;//store opration symbol
		Nodes* left;
		Nodes* right;
		bool is_num;//determine this node is number or symbol,true is num,false is symbol
//==============
//constructor
//=============
		Nodes(char input_op):op(input_op),left(NULL),right(NULL),is_num(false){//create symbol node
			assert((op=='+')||(op=='-')||(op=='*')||(op=='/'));//make sure input is right op		
		}
		Nodes(float input_num):num(input_num),left(NULL),right(NULL),is_num(true){}//create num node
		~Nodes(){
			delete left;
			delete right;
		}
};
//==============
//tree defination
//==============
class expression_tree{
	public:
		stack<Nodes*> exp_stack;
		void add(Nodes* n){
			if(!n->is_num){
				assert(exp_stack.size()>=2);
				n->left=exp_stack.top();
				exp_stack.pop();
				n->right=exp_stack.top();
				exp_stack.pop();
				exp_stack.push(n);
			}
			else{
				exp_stack.push(n);
			}
		}
		
		void clear(){
			while(!exp_stack.empty()){
				delete exp_stack.top();
				exp_stack.pop();
			}
		}	
		bool expression_legal(){
			if(exp_stack.size()==1)
				return true;
			else
				return false;
		}
		void postorder_helper(vector<Nodes*>* exp,Nodes* n){
			if(n!=NULL){
				assert( ((n->left==NULL)&&(n->right==NULL)&&(n->is_num))||((n->left!=NULL)&&(n->right!=NULL)&&(!n->is_num)) );
				postorder_helper(exp,n->left);
				postorder_helper(exp,n->right);
				exp->push_back(n);
			}
		}
			
		vector<Nodes*>* postorder(){
			assert(expression_legal());
			vector<Nodes*>* exp=new vector<Nodes*>;
			postorder_helper(exp,exp_stack.top());
			return exp;
		}		
		
		void inorder_helper(Nodes* n){
			if(n!=NULL){
				assert( ((n->left==NULL)&&(n->right==NULL)&&(n->is_num))||((n->left!=NULL)&&(n->right!=NULL)&&(!n->is_num)) );
				if(!n->is_num)
					cout<<"( ";
				inorder_helper(n->left);
				if(n->is_num)
					cout<<n->num;
				else
					cout<<' '<<n->op<<' ';
				inorder_helper(n->right);
				if(!n->is_num)
					cout<<" )";
			}
		}
		void inorder(){
			assert(expression_legal());
			Nodes* n=exp_stack.top();
			inorder_helper(n);
			cout<<endl;
		}
};	 
