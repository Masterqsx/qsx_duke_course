#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

//YOUR CODE GOES HERE!
template<typename T>

class Matrix {
	private:
		int numRows;
		int numColumns;
		std::vector< std::vector<T> > rows;
	public:
		Matrix(){
			numRows=0;
			numColumns=0;
			rows.resize(0);
		}
			
		Matrix(int r, int c){
			numRows=r;
			numColumns=c;
			rows.resize(r);
			for(int i=0;i<r;i++){
				rows[i].resize(c);
			}
		}

		Matrix(const Matrix & rhs){
			numRows=rhs.numRows;
			numColumns=rhs.numColumns;
			rows.resize(numRows);
			for(int i=0;i<numRows;i++){
				rows[i].resize(numColumns);
				rows[i]=rhs.rows[i];
			}
		}
		
		~Matrix(){
			for(int i=0;i<numRows;i++){
				rows[i].clear();
			}
			rows.clear();
		}

		Matrix & operator=(const Matrix & rhs){
			if(this!=&rhs){
				for(int i=0;i<numRows;i++){
					rows[i].clear();
				}		
				rows.clear();
				
				numRows=rhs.numRows;
				numColumns=rhs.numColumns;
				
				rows.resize(numRows);
				for(int j=0;j<numRows;j++){
						rows[j].resize(numColumns);
						rows[j]=rhs.rows[j];
				}
			}
			return *this;
	}			

		int getRows() const{
			return numRows;
		}
		
		int getColumns() const{
			return numColumns;
		}
	
		const vector<T> & operator[](int index) const{
			assert((index>=0)&&(index<numRows));
			return rows[index];
		}
	
		std::vector<T> & operator[](int index){
			assert((index>=0)&&(index<numRows));
			return rows[index];
		}

		bool operator==(const Matrix & rhs) const {
			if(numRows!=rhs.numRows)
				return 0;
			if(numColumns!=rhs.numColumns)
				return 0;
			for(int i=0;i<numRows;i++){
				if(rows[i]!=rhs.rows[i])
					return 0;
			}
			return 1;
		}
		
		Matrix operator+(const Matrix & rhs) const{
			assert((numRows==rhs.numRows)&&(numColumns==rhs.numColumns));
			Matrix sum(numRows,numColumns);
			for(int i=0;i<numRows;i++){
				for(int j=0;j<numColumns;j++){
					sum.rows[i][j]=rows[i][j]+rhs.rows[i][j];
				}
			}
			return sum;
		}	
	
};
template<typename T>
std::ostream & operator<<(std::ostream & s, const vector<T> & vec){
	s<<"{";
	for(unsigned int i=0;i<vec.size()-1;i++){
		s<<vec[i]<<", ";
	}
	s<<vec[vec.size()-1]<<"}";
	return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs){
		s<<"[ ";
		for(int i=0;i<rhs.getRows()-1;i++){
				s<<rhs[i]<<",\n";
		}
		if(rhs.getRows()>=1)
			s<<rhs[rhs.getRows()-1]<<" ]";
		else
			s<<" ]";
		return s;
}

#endif
