#ifndef _equation_tree_
#define _equation_tree_
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<stack>
#include<string>
#include<map>
#include<vector>
#include<assert.h>
using namespace std;
class Nodes{
	public:
		float num;
		int flag;
		string v_name;
    char op;
		string e_name;
		int paras_size;
		stack<Nodes*> equ_stack;
		vector<pair<string,Nodes*> > paras;
		vector<float> paras_num;

    virtual void assign(float input_num){}
   	virtual Nodes* copy(Nodes* o,Nodes* old_equ){
			return NULL;
		}
		virtual void add(Nodes* n){}
		virtual void para_assign(float input_num){}
		vector<Nodes*> next;
		Nodes():num(0),flag(0){}
		Nodes(float input_num):num(input_num),flag(0){}
		virtual float eval(){
			return num;
		}
		virtual ~Nodes(){
			for(vector<Nodes*>::iterator it=next.begin();it!=next.end();it++){
				delete *it;
			}
		}
};

class variable:public Nodes{
	public:
		variable(string input_name):Nodes(){
			flag=1;
			v_name=input_name;
		}
   	virtual Nodes* copy(Nodes* o,Nodes* old_equ){
			return NULL;
		}
		virtual void add(Nodes* n){}
		virtual void para_assign(float input_num){}

		virtual void assign(float input_num){
			num=input_num;
		}
		virtual float eval(){
			return num;
		}
};

class symbol:public Nodes{
	public:
		symbol():Nodes(){}
		symbol(char input_op):Nodes(){
			flag=2;
			next.push_back(NULL);next.push_back(NULL);
			op=input_op;
		}
		virtual void assign(float input_num){}	
		virtual Nodes* copy(Nodes* o,Nodes* old_equ){
			return NULL;
		}
		virtual void add(Nodes* n){}
		virtual void para_assign(float input_num){}
		
		virtual float eval(){
			assert((next[0]!=NULL)&&(next[1]!=NULL));
			switch(op){
				case '+':
					return next[0]->eval()+next[1]->eval();
				case '-':
					return next[0]->eval()-next[1]->eval();
				case '*':
					return next[0]->eval()*next[1]->eval();
				case '/':
					assert(next[1]->eval()!=0);
					return next[0]->eval()/next[1]->eval();
				default:
					cerr<<"Unknown op"<<endl;
					abort();
			}
		}
};

class equation:public Nodes{
	public:
		equation(string input_name,int input_size):Nodes(){
			flag=3;
			e_name=input_name;
			paras_size=input_size;
		}
    virtual void assign(float input_num){}
		
		Nodes* copy(Nodes* o,Nodes* old_equ){
			int i,j,k;
			stack<Nodes*> temp;
			switch(o->flag){
				case 0:
					return o;
				case 1:
					return NULL;//could pass the equation
				case 2:{
					Nodes* n=new symbol(o->op);
					for(i=0;i<2;i++){
						switch(o->next[i]->flag){
							case 0:
								n->next[i]=o->next[i];
								break;
							case 1:
								for(j=0;j<old_equ->paras_size;j++){
									if(old_equ->paras[j].second==o->next[i]){
										for(k=j+1;k<old_equ->paras_size;k++){
											temp.push(equ_stack.top());
											equ_stack.pop();
										}
										n->next[i]=equ_stack.top();
										for(k=j+1;k<old_equ->paras_size;k++){
											equ_stack.push(temp.top());
											temp.pop();
										}
									}
								}
								assert(n->next[i]!=NULL);
								break;
							case 2:
								n->next[i]=copy(o->next[i],old_equ);
								break;
							default:
								cerr<<"a equation tree will not have equation pointer"<<endl;
								abort();
						}
					}
					return n;
				}
				default:
					cerr<<"a equation tree will not have equation pointer"<<endl;
					abort();
			}
		}		
			
		void add(Nodes* n){
			switch(n->flag){
				case 0:
					equ_stack.push(n);
					break;
				case 1:
					paras.push_back(pair<string,Nodes*>(n->v_name,n));
					equ_stack.push(n);
					break;
				case 2:
					assert(equ_stack.size()>=2);
					n->next[0]=equ_stack.top();
					equ_stack.pop();
					n->next[1]=equ_stack.top();
					equ_stack.pop();
					equ_stack.push(n);
					break;
				case 3:{
					assert(equ_stack.size()>=(unsigned)n->paras_size);			
					assert((unsigned)n->paras_size==n->paras.size());
					Nodes* equ_tree=copy(n->equ_stack.top(),n);
					if(equ_tree==NULL)
						break;
					for(int i=0;i<n->paras_size;i++){
						equ_stack.pop();
					}
					equ_stack.push(equ_tree);
					break;
				}
				default:
					cerr<<"Wrong Nodes flag"<<endl;
					abort();
			}
		}
		virtual void para_assign(float input_num){
			paras_num.push_back(input_num);
		}//para_num input sequence should same as from left to right
		virtual float eval(){
			assert(paras_num.size()==paras.size());	
			assert((unsigned)paras_size==paras.size());
			assert(equ_stack.size()==1);
			for(unsigned int i=0;i<paras.size();i++){
				paras[i].second->assign(paras_num[paras.size()-1-i]);
			}
			return equ_stack.top()->eval();
		}
};	
#endif			
