#pragma once
#include "Proxy.h"
#include <random>
#include <math.h>

class Matrix
{
	friend class Matrix;
	double** data;

	static double randNum(double min, double max);
	
	void init(size_t _rows, size_t _cols);

	public:
	void initRandom(size_t _rows, size_t _cols, double min, double max);

	public:
		size_t rows, cols;

		Matrix();
		//~Matrix();
		Matrix(size_t _rows, size_t _cols);
		Matrix(const Matrix& other);
		Matrix(double** _data, size_t _rows, size_t _cols);
		Matrix(const Matrix& a, const Matrix& b);

		Matrix transpose();

		void dispose();

		Proxy operator[](int index);
		Matrix& operator+=(const Matrix& rhs);
		Matrix& operator-=(const Matrix& rhs);
		Matrix& operator^=(const Matrix& rhs);
		Matrix& operator*=(double value);

		Matrix operator+(const Matrix& rhs);
		Matrix operator-(const Matrix& rhs);
		Matrix operator^(const Matrix& rhs);


		Matrix operator*(const Matrix& rhs);
		Matrix operator*(double value);
};