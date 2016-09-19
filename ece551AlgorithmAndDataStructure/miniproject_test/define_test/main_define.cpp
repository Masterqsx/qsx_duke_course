#include<iostream>
#include<cstdlib>
#include<cstdio>
#include"define_parsing.h"
#include<map>
#include"eval_parsing.h"
#include<string>
#include"equation_tree.h"
#include<vector>
#include"parsing.h"
int main(){
	map<string,Nodes*> function_map;
	vector<string> command_list;
	string c0("define"); string c1("eval");
	command_list.push_back(c0);
	command_list.push_back(c1);
	string shell_input;
	while(!getline(cin,shell_input).eof()){
		parsing(shell_input,command_list,function_map);
	}
	return 0;
}
