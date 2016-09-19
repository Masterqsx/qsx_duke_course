#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <fstream>
#include <iostream>
using namespace std;
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
 ifstream input;
	int c;
	input.open(fname);
	if(input.fail()){
		perror("Could not open file");
		return NULL;
	}
	uint64_t * c_table=new uint64_t[257]();//initialize 0 in all block
	while((c=input.get())!=EOF){
	//	d=c;
		c_table[c]++;
	}
	c_table[256]++;
	input.close();
	return c_table;
/*
	uint64_t* a=new uint64_t[257]();
	FILE* f=fopen(fname,"r");
	if(f==NULL){
		return NULL;
	}
	int c;
	while((c=fgetc(f))!=EOF){
		a[c]++;
	}
	a[256]=1;
	fclose(f);
	return a;*/
}
