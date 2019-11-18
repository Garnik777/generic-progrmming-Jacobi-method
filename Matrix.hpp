#ifndef _MATRIX_HPP__
#define _MATRIX_HPP__
#include <cstddef>
template<typename T>
class Matrix
{
    private:
	std::size_t mColCount;
	std::size_t mRowCount;
	T * mData;
	
    public:
	typedef T element_type;
	void initialize( const std::size_t r, const std::size_t c )
	{
		mRowCount = r;
		mColCount = c;
		mData = new T[r*c];
	}

	void setvalue( const std::size_t i, const std::size_t j,const  T  e)
	{
		mData[i* mColCount + j] = e;
	}
	
	T & getvalue( const std::size_t i , const std::size_t j) const
	{
		return mData[ i * mColCount + j ];
	}
	
	 T & operator()(std::size_t i, std::size_t j) const
	{
		return mData[i * mColCount + j];
	}

	std::size_t getCol() const
	{
		return mColCount;
	}

	std::size_t getRow() const
	{
		return mRowCount;
	}
};

#endif

