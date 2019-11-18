#include "Matrix.hpp"
#include "Interface.hpp"
#include<cassert>
#include<limits>  //for numeric_limits
#include<cstddef> //std::size_t
#include<fstream>
#include<iostream> 
#include<iomanip> //for setw()


template<typename T>
void readMatrix(Matrix<T>& matrix, std::ifstream& like_pipe )
{
	using MI = interface<Matrix<T>>;
	assert( like_pipe.is_open() );
	std::size_t r= std::numeric_limits<std::size_t>::max();
	like_pipe >> r;
	assert(r < std::numeric_limits<T>::max() );
	assert(r > 0);
	assert( like_pipe.is_open() );
	std::size_t c = std::numeric_limits<std::size_t>::max();
	like_pipe >> c;
	assert(c < std::numeric_limits<T>::max() );
	assert(c > 0);
	typename MI::element_type x = std::numeric_limits<T>::max();
	matrix.initialize(r,c);
	for( std::size_t i = 0; i < MI::getRow(matrix); ++i)
	{
		for( std::size_t j=0; j< MI::getCol(matrix); ++j)
		{
			like_pipe >> x; //OK version
			assert( x < std::numeric_limits<T>::max());
		MI::set_element(matrix,i,j,x);
		}//end for(j;j;j)
			std::cout << std::endl;
	}//end for(i;i;i)
}


template<typename T>
T myRound( T var)
{
	T value = (int)(var * 10000);
	return (T)value/10000;
}

template<typename T>
void writeMatrix(const Matrix<T>& matrix , std::ofstream & like_pipe)
{
	using MI = interface<Matrix<T>>;
	assert(like_pipe.good());
	like_pipe<< MI::getRow(matrix) << " ";
	assert(like_pipe.good());
	like_pipe<< MI::getCol(matrix) << std::endl;

	for(std::size_t i = 0; i < MI::getRow(matrix); ++i)
	{
		for( std::size_t j = 0; j< MI::getCol(matrix); ++j)
		{
			like_pipe << MI::get_element(matrix,i,j); //OK version
		//	like_pipe.put( matrix.getvalue(i,j));	
		}//end for(j;j;j)
		like_pipe << std::endl;
	}//end for(i;i;i)	
}

template<typename T>
void jacobiMethod(const Matrix<T>& a,
		  const Matrix<T>& b,
			Matrix<T>& x)
{
	using MI = interface<Matrix<T>>;
	std::size_t single_col= 0;
	x.initialize(a.getRow(), b.getCol()); //first iteration x(0,0,...0)
	for ( std::size_t i = 0; i < MI::getRow(a); ++i){
		MI::set_element(x,i,single_col,0);
	}//end for(i;i;i)
	std::size_t count = 0;
	while( count < 50){
	for ( std::size_t i= 0; i< MI::getRow(a); ++i){ //finding solution
		typename MI::element_type sum = 0;
		typename MI::element_type  e = 0;
		assert( e < std::numeric_limits<T>::max());	
		for( std::size_t j =0; j< MI::getCol(a); ++j){
		 	if( i != j){
				sum += MI::get_element(x,i,single_col) * MI::get_element(a,i,j);
			//	assert( sum < std::numeric_limits<T>::max());
			}//end if
		}//end for(j;j;j
				e = MI::get_element(b,i,single_col) - sum;
				e =e/MI::get_element(a,i,i); //
				e = myRound(e); //under construction
				MI::set_element(x,i, single_col, e);
			// 	e =-1/a.getvalue(i,i)* (sum - b.getvalue(i,single_col));
			//	e =e/a.getvalue(i,i); //
			//	x.setvalue(i, single_col, e);
			
		}//end for(i;i;i)
	 count++;
	}//end while

}

int main()
{	
	Matrix<float> a;
	Matrix<float> b;
	Matrix<float> x;
	std::ifstream A("A.txt"), B("B.txt");
	std::ofstream X("x.txt");
	readMatrix(a,A); 
	readMatrix(b,B);
	x.initialize(a.getRow(), b.getCol());
	jacobiMethod(a, b, x);
	writeMatrix(x, X);
	return 0;
}
