#include<string>
#include<cstdlib>
#include<cstdio>

using namespace std;
bool is_num_pure(char n){
	if(((n-'0')>=0)&&((n-'0')<10))
		return true;
	else
		return false;
}

bool is_num_dot(char n){
	if(n=='.')
		return true;
	else
		return false;
}

bool is_num_symbol(char n){
	if((n=='+')||(n=='-'))
		return true;
	else
		return false;
}

bool is_blank(char n){
	if((n==' ')||(n=='(')||(n==')'))
		return true;
	else
		return false;
}

bool is_valid(char n){
	if((((n-'0')>=0)&&((n-'0')<10))||(n=='+')||(n=='-')||(n=='*')||(n=='/')||(n=='.')){
		return true;
	}
	else
		return false;
}

bool is_op(char n){
	if( (n=='+')||(n=='-')||(n=='*')||(n=='/') )
		return true;
	else
		return false;
}


void string_translation(string line,expression_tree &expr){
	string temp;int flag=0;
	for(int i=line.size()-1;i>=0;i--){
			switch(flag){
				case 0:
					if(is_num_pure(line[i])){
						flag=1;
						temp=line[i]+temp;
						break;
					}
					else if(is_op(line[i])){
						expr.add(new Nodes(line[i]));
						break;
					}
					else if(is_blank(line[i])){
						break;
					}
					else{
						cerr<<"Wrong expression input"<<endl;
						abort();
					}
				case 1:
					if(is_num_pure(line[i])){
						temp=line[i]+temp;
						break;
					}
					else if(is_num_symbol(line[i])){
						flag=3;
						temp=line[i]+temp;
						break;
					}
					else if(is_num_dot(line[i])){
						flag=2;
						temp=line[i]+temp;
						break;
					}
					else if(is_blank(line[i])){
						flag=0;
						expr.add(new Nodes(strtof(temp.c_str(),NULL)));
						temp.clear();
						break;
					}
					else{
						cerr<<"Wrong expression input"<<endl;
						abort();
					}
				case 2:
					if(is_num_pure(line[i])){
						temp=line[i]+temp;
						break;
					}
					else if(is_num_symbol(line[i])){
						flag=3;
						temp=line[i]+temp;
						break;
					}
					else if(is_blank(line[i])){
						flag=0;
						expr.add(new Nodes(strtof(temp.c_str(),NULL)));
						temp.clear();
						break;
					}
					else{
						cerr<<"Wrong expression input"<<endl;
						abort();
					}
				case 3:
					if(is_blank(line[i])){
						flag=0;
						expr.add(new Nodes(strtof(temp.c_str(),NULL)));
						temp.clear();
						break;
					}
					else{
						cerr<<"Wrong expression input"<<endl;
						abort();
					}
			}		
	}
	if((flag==1)||(flag==2)){
		flag=0;
		expr.add(new Nodes(strtof(temp.c_str(),NULL)));
		temp.clear();
	}
}



