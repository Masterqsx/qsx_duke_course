#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray() {
	data=NULL;
	numElements=0;
}
IntArray::IntArray(int n) {
	numElements=n;
	data=new int[n];
}

IntArray::IntArray(const IntArray & rhs){
	numElements=rhs.numElements;
	data=new int[numElements];
	for(int i=0;i<numElements;i++)
	{
		data[i]=rhs.data[i];
	}
	

}

IntArray::~IntArray() {
	
	delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
	delete[] data;
	data=NULL;
	data=new int[numElements];
	for(int i=0;i<numElements;i++)
	{
		data[i]=rhs.data[i];
	}
	numElements=rhs.numElements;
	return *this;
}
const int & IntArray::operator[](int index) const {
	assert( (index>=0)&&(index<numElements) );
	return data[index];
}
int & IntArray::operator[](int index) {
	assert( (index>=0)&&(index<numElements) );
	return data[index];
}

int IntArray::size() const {
	return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
	if(numElements!=rhs.numElements)
	{
		return 0;
	}
	else
	{
		for(int i=0;i<numElements;i++)
		{
			if(data[i]!=rhs.data[i])
			{
				return 0;
			}
		}
	}
	return 1;	
}

bool IntArray::operator!=(const IntArray & rhs) const {
	if(*this==rhs)
	{
		return 0;
	}
	else
		return 1;	
}


std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
	s<<"{";
	for(int i=0;i<rhs.size()-1;i++)
	{
		s<<rhs[i]<<", ";
	}
	s<<rhs[rhs.size()-1]<<"}";//could not use i here
	return s;
	

}
