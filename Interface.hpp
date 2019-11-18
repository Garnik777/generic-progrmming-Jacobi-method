#ifndef _INTERFACE_HPP__
#define _INTERFACE_HPP__
#include "Matrix.hpp"
#include <cstddef>
#include <iostream>

template <typename T> struct interface {};

template <typename T>
struct interface<Matrix<T> > 
{
	typedef typename Matrix<T>::element_type element_type;
	static element_type get_element(const Matrix<T>& a, std::size_t i, std::size_t j) {
		return a(i, j);
		//return a.getvalue(i,j);
	}

	static void set_element(Matrix<T>& a, std::size_t i, std::size_t j, T x) {
		a(i, j) = x;
		//a.setvalue(i,j) = x;
	}

	static std::size_t getRow(const Matrix<T>& a)
	{
		return a.getRow();
	}

	static std::size_t getCol(const Matrix<T>& a)
	{
		return a.getCol();
	}
};

#endif
