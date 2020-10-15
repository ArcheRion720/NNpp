#pragma once
#include "Proxy.h"
#include <random>
#include <math.h>

class Matrix
{
	typedef double callback(double item);

	struct IncompatibleMatrixException : public std::exception
	{
		const char* what() const throw()
		{
			return "Attempt to execute operation on incompatible matrices";
		}
	};

	friend class Matrix;
	double** data;

	static double randNum(double min, double max);

	void initEmpty(size_t _rows, size_t _cols);
	void initFill(size_t _rows, size_t _cols, double value = 0);

	public:
		void initRandom(size_t _rows, size_t _cols, double min, double max);

	public:
		size_t rows, cols;

		Matrix();
		~Matrix();
		Matrix(size_t _rows, size_t _cols);
		Matrix(const Matrix& other);

		double& operator()(size_t index)
		{

		}

		Proxy operator[](size_t index) const;

		Matrix& operator=(const Matrix& matrix);

		Matrix& operator+=(const Matrix& rhs);
		Matrix& operator-=(const Matrix& rhs);
		Matrix& operator^=(const Matrix& rhs);
		Matrix& operator*=(double value);

		Matrix operator+(const Matrix& rhs);
		Matrix operator-(const Matrix& rhs);
		Matrix operator^(const Matrix& rhs);

		Matrix operator*(const Matrix& rhs);
		Matrix operator*(double value);

		Matrix operator~();

		void callOnElements(callback _call);

		inline void allocData(size_t _rows, size_t _cols);
		inline void copyData(const Matrix& matrix);
		inline void disposeData();
};