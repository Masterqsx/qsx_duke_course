#include<iostream>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<fstream>
#include"expression_tree.h"
#include"string_translation.h"

using namespace std;
int main(int args,char **argv){
	ifstream input;
	string line;
	expression_tree expr;
	if(args!=2)
		return EXIT_FAILURE;
	input.open(argv[1]);
	if(input.fail())
		return EXIT_FAILURE;
	while(!getline(input,line).eof()){
		string_translation(line,expr);
		expr.inorder();
		expr.clear();	
	}	
	input.close();
	return EXIT_SUCCESS;
}
