#ifndef _equation_tree_
#define _equation_tree_
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<stack>
#include<string>
#include<map>
#include<math.h>
#include<vector>
#include<assert.h>
using namespace std;
class Nodes{
	public:
		double num;
		int flag;
		string v_name;
    string op;
		string e_name;
		int paras_size;
		stack<Nodes*> equ_stack;
		vector<pair<string,Nodes*> > paras;
		vector<double> paras_num;

    virtual void assign(double input_num){}
   	virtual Nodes* copy(Nodes* o,Nodes* old_equ){
			return NULL;
		}
		virtual void add(Nodes* n){}
		virtual void para_assign(double input_num){}
		vector<Nodes*> next;
		Nodes():num(0),flag(0){}
		Nodes(double input_num):num(input_num),flag(0){}
		virtual double eval(){
			return num;
		}
		virtual ~Nodes(){}
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
		virtual void para_assign(double input_num){}

		virtual void assign(double input_num){
			num=input_num;
		}
		virtual double eval(){
			return num;
		}
};

class symbol:public Nodes{
	public:
		symbol():Nodes(){}
		symbol(string input_op):Nodes(){
			flag=2;
			next.push_back(NULL);next.push_back(NULL);
			op=input_op;
			if(op=="sqrt")
				paras_size=1;
			else
				paras_size=2;
		}
		virtual void assign(double input_num){}	
		virtual Nodes* copy(Nodes* o,Nodes* old_equ){
			return NULL;
		}
		virtual void add(Nodes* n){}
		virtual void para_assign(double input_num){}
		
		virtual double eval(){
			assert(next[0]!=NULL);
			if(op!="sqrt")
				assert(next[1]!=NULL);
			if(op=="+")
					return next[0]->eval()+next[1]->eval();
			else if(op=="-")
					return next[0]->eval()-next[1]->eval();
			else if(op=="*")
					return next[0]->eval()*next[1]->eval();
			else if(op=="/"){
					assert(next[1]->eval()!=0);
					return next[0]->eval()/next[1]->eval();
			}
			else if(op=="sqrt"){
					assert(next[0]->eval()>=0);
					return (double)sqrt(next[0]->eval());
			}
			else if(op=="pow"){
					return (double)pow(next[0]->eval(),next[1]->eval());
			} 
			else{
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
		~equation(){
				destroy(equ_stack.top());
				vector<pair<string,Nodes*> >::iterator it;
				for(it=paras.begin();it!=paras.end();it++){
					delete it->second;
				}
		}
    virtual void assign(double input_num){}
		void destroy(Nodes* wfd){
			if(wfd->flag==2){
				vector<Nodes*>::iterator it;
				for(it=wfd->next.begin();it!=wfd->next.end();it++){
					if(*it!=NULL)
						destroy(*it);
				}
			}		
			if(wfd->flag!=1){
				delete wfd;
			}
    }
		Nodes* copy(Nodes* o,Nodes* old_equ){
			int i,j,k;
			stack<Nodes*> temp;
			switch(o->flag){
				case 0:{
					Nodes* n=new Nodes(o->num);
					return n;
				}
				case 1:
					return NULL;//could pass the equation
				case 2:{
					Nodes* n=new symbol(o->op);
					for(i=0;i<o->paras_size;i++){
						switch(o->next[i]->flag){
							case 0:{
								Nodes* n_constant=new Nodes(o->next[i]->num);
								n->next[i]=n_constant;
								break;
							}
							case 1:
								for(j=0;j<old_equ->paras_size;j++){
									if(old_equ->paras[j].second==o->next[i]){
										for(k=0;k<j;k++){
											temp.push(equ_stack.top());
											equ_stack.pop();
										}
										n->next[i]=equ_stack.top();
										for(k=0;k<j;k++){
											equ_stack.push(temp.top());
											temp.pop();
										}
										break;
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
					equ_stack.push(n);
					break;
				case 2:{
					assert(equ_stack.size()>=(unsigned)n->paras_size);
					for(int j=0;j<n->paras_size;j++){
						n->next[j]=equ_stack.top();
						equ_stack.pop();
					}
					equ_stack.push(n);
					break;
				}
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
		virtual void para_assign(double input_num){
			paras_num.push_back(input_num);
		}//para_num input sequence should same as from left to right
		
		
		virtual double eval(){
			assert(paras_num.size()==paras.size());	
			assert((unsigned)paras_size==paras.size());
			assert(equ_stack.size()==1);
			for(unsigned int i=0;i<paras.size();i++){
				paras[i].second->assign(paras_num[i]);
			}
			return equ_stack.top()->eval();
		}
};	
#endif			
