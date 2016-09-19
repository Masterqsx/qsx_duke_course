#include "IntMatrix.h"

IntMatrix::IntMatrix(){
	rows=NULL;
	numRows=0;
	numColumns=0;
}
IntMatrix::IntMatrix(int r, int c) {
	numRows=r;
	numColumns=c;
	rows=new IntArray*[r];
	for(int i=0;i<r;i++)
	{
		rows[i]=new IntArray(c);
	}	
}

IntMatrix::IntMatrix(const IntMatrix & rhs)  {
	numRows=rhs.numRows;
	numColumns=rhs.numColumns;
	rows=new IntArray*[numRows];
	for(int k=0;k<numRows;k++)
	{
		rows[k]=new IntArray(numColumns);
		*rows[k]=*rhs.rows[k];
	}	  
}

IntMatrix::~IntMatrix() {
	for(int i=0;i<numRows;i++)
	{
		delete rows[i];
	}
	delete[] rows;
}
IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
  if(this!=&rhs) {	
   for(int i=0;i<numRows;i++) {
      delete rows[i];
    }
    delete[] rows;
		 numRows=rhs.numRows;
    numColumns=rhs.numColumns;
    
    rows=new IntArray*[numRows];
    for(int k=0;k<numRows;k++) {
      rows[k]=new IntArray(*rhs.rows[k]);
    }
  }
  return *this;
}
int IntMatrix::getRows() const {
	return numRows;
}
int IntMatrix::getColumns() const {
	return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
	assert((index>=0)&&(index<numRows));
	return *rows[index];
}
IntArray & IntMatrix::operator[](int index){
	assert((index>=0)&&(index<numRows));
	return *rows[index];
}



bool IntMatrix::operator==(const IntMatrix & rhs) const {
	if(numRows!=rhs.numRows)
		return 0;
	if(numColumns!=rhs.numColumns)
		return 0;
	for(int i=0;i<numRows;i++)
	{
	  if(*rows[i]!=*rhs.rows[i])
	  {
		return 0;
	  }
	}
	return 1;

}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
	assert((numRows==rhs.numRows)&&(numColumns==rhs.numColumns));
	IntMatrix sum(numRows,numColumns);
	for(int i=0;i<numRows;i++)
	{
	  for(int j=0;j<numColumns;j++)
	  {
		(*sum.rows[i])[j]=(*rows[i])[j]+(*rhs.rows[i])[j];
	  }
	}
	return sum;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
	s<<"[ ";
	for(int i=0;i<rhs.getRows()-1;i++)
	{
		s<<rhs[i]<<",\n";
	}
	if(rhs.getRows()>=1)
		s<<rhs[rhs.getRows()-1]<<" ]";
	else
		s<<" ]";
	return s;
}
