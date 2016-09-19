#include<iostream>
#include<exception>
#include<typeinfo>
#include<stdexcept>
#include"bstmap.h"
#include"map.h"

int main(){
	BstMap<int,int>* map1=new BstMap<int,int>;
	map1->add(2,1);
	map1->add(4,2);
	map1->add(1,3);
	map1->add(7,4);
	map1->add(3,5);
	map1->add(9,6);
	map1->add(-1,7);
	map1->add(88,8);
	map1->add(17,9);
	map1->add(-23,10);
	map1->add(16,11);
	map1->add(44,12);
	map1->add(77,13);
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
	map1->remove(77);
	map1->remove(4);	
	map1->add(2,1);
	map1->add(4,2);
	map1->add(1,3);
	map1->add(7,4);
	map1->add(3,5);
	map1->add(9,6);
	map1->add(-1,7);
	map1->add(88,8);
	map1->add(17,9);
	map1->add(-23,10);
	map1->add(16,11);
	map1->add(44,12);
	map1->add(77,13);
	map1->remove(2);
	map1->remove(16);
  map1->remove(-1);

//	std::cout<<map1->lookup(-1)<<std::endl;
	map1->preorder_print();
	map1->inorder_print();
	map1->postorder_print();
	delete map1;	
	return 0;
}	
