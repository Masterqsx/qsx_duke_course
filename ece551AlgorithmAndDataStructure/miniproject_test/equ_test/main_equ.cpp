#include<iostream>
#include "equation_tree.h"

int main(){
	string v0("x");
  string v1("y");
	string v2("z");
///////////////////////////////////
	string func0_name("g");
  int func0_size=2;
	Nodes* func0=new equation(func0_name,func0_size);
	Nodes* func0_v0=new variable(v0);
	Nodes* func0_v1=new variable(v1);
	Nodes* func0_v2=new Nodes(1.5);
	Nodes* func0_sym1=new symbol('+');
	Nodes* func0_sym0=new symbol('*');
	func0->add(func0_v2);
  func0->add(func0_v1);
  func0->add(func0_v0);
	func0->add(func0_sym1);
	func0->add(func0_sym0);
///////////////////////////////////
	string func1_name("h");
	int func1_size=3;
	Nodes* func1=new equation(func1_name,func1_size);
	Nodes* func1_v0=new variable(v0);
	Nodes* func1_v1=new variable(v1);
	Nodes* func1_v2=new variable(v2);
	Nodes* func1_sym0=new symbol('/');
	func1->add(func1_v2);
	func1->add(func1_v1);
	func1->add(func1_v0);
	func1->add(func0);
	func1->add(func1_sym0);
//////////////////////////////////	
	func1->para_assign(1);
	func1->para_assign(-2);
	func1->para_assign(3);
	cout<<func1->eval()<<endl;
	func0->para_assign(2);
	func0->para_assign(0);
	cout<<func0->eval()<<endl;
	
	return 0;
}
