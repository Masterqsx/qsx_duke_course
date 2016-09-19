#include<iostream>
#include<exception>
#include<typeinfo>
#include<stdexcept>
#include"bstset.h"
#include"set.h"

int main(){
	BstSet<int>* map1=new BstSet<int>;
	map1->add(2);
	map1->add(4);
	map1->add(1);
	map1->add(7);
	map1->add(3);
	map1->add(9);
	map1->add(-1);
	map1->add(88);
	map1->add(17);
	map1->add(-23);
	map1->add(16);
	map1->add(44);
	map1->add(77);
	map1->remove(2);
	map1->remove(16);
  map1->remove(-1);
	map1->remove(-1);
	map1->remove(1);
	map1->remove(7);
	map1->remove(3);
	map1->remove(9);
	map1->remove(88);
	map1->remove(17);
	map1->remove(-23);
	map1->remove(44);
	map1->remove(4);
//	map1->remove(77);
//	std::cout<<map1->contains(77)<<std::endl;
	map1->preorder_print();
	map1->inorder_print();
	map1->postorder_print();
	delete map1;	
	return 0;
}	
