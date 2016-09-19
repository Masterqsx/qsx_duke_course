#ifndef _eval_parsing_
#define _eval_parsing_
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<assert.h>
#include<string>
#include<map>
#include<stack>
#include"check_list.h"
#include<math.h>
void eval_parsing(string input,map<string,Nodes*> &function_map){
	char *command_temp=strdup(input.c_str());
	strtok(command_temp," ()");

	char *command_element=NULL;
  stack<char *> equ_Nodes;
	while((command_element=strtok(NULL," ()"))!=NULL){
		equ_Nodes.push(command_element);
	}
	stack<double> eval_stack;
	Nodes* func=NULL;
	while(equ_Nodes.size()>0){
		func=NULL;	
		if(is_symbol(equ_Nodes.top())){
			if(strcmp(equ_Nodes.top(),"sqrt")==0){
				assert(eval_stack.size()>=1);
				double operand=eval_stack.top();
				eval_stack.pop();
				eval_stack.push((double)sqrt(operand));
			}
			else{
				assert(eval_stack.size()>=2);
				double left=eval_stack.top();
				eval_stack.pop();
				double right=eval_stack.top();
				eval_stack.pop();
				if(strcmp(equ_Nodes.top(),"+")==0){
					eval_stack.push(left+right);
				}
				else if(strcmp(equ_Nodes.top(),"-")==0){
					eval_stack.push(left-right);
				}
				else if(strcmp(equ_Nodes.top(),"*")==0){
					eval_stack.push(left*right);
				}
				else if(strcmp(equ_Nodes.top(),"/")==0){
					assert(right!=0);
					eval_stack.push(left/right);
				}
				else if(strcmp(equ_Nodes.top(),"pow")==0){
					eval_stack.push((double)pow(left,right));
				}
			}
			equ_Nodes.pop();
		}
		else if(is_num(equ_Nodes.top())){
			eval_stack.push(strtod(equ_Nodes.top(),NULL));
			equ_Nodes.pop();
		}
		else if((func=is_exist_function(equ_Nodes.top(),function_map))!=NULL){
			assert(eval_stack.size()>=(unsigned)func->paras_size);
			func->paras_num.clear();
			for(int i=0;i<func->paras_size;i++){
				func->para_assign(eval_stack.top());
				eval_stack.pop();
			}
			eval_stack.push(func->eval());
			equ_Nodes.pop();
		}
		else{
			cerr<<"Wrong evaluate input"<<endl;
			abort();
		}
	}
	if(eval_stack.size()!=1){
		cerr<<"Wrong input evaluate parameter"<<endl;
		abort();
	}
	assert(eval_stack.size()==1);
	cout<<"The result of  "<<input<<"  is  "<<eval_stack.top()<<endl<<endl;
  free(command_temp);
}
#endif
