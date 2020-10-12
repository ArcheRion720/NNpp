#include "Matrix.h"
#include <time.h>

double Matrix::randNum(double min, double max)
{
	static std::default_random_engine rng(std::random_device{}());
	std::uniform_real_distribution<double> dist(min, max);

	return dist(rng);
}

void Matrix::init(size_t _rows, size_t _cols)
{
	rows = _rows;
	cols = _cols;

	data = new double* [_rows];
	for (size_t i = 0; i < _rows; i++)
	{
		data[i] = new double[_cols];
		for (size_t j = 0; j < _cols; j++)
		{
			data[i][j] = 0;
		}
	}
}

void Matrix::initRandom(size_t _rows, size_t _cols, double min, double max)
{
	rows = _rows;
	cols = _cols;

	data = new double* [_rows];
	for (size_t i = 0; i < rows; i++)
	{
		data[i] = new double[_cols];
		for (size_t j = 0; j < cols; j++)
		{
			data[i][j] = randNum(min, max);
		}
	}
}

Matrix::Matrix() : rows(0), cols(0), data(nullptr)
{ }

Matrix::Matrix(size_t _rows, size_t _cols) : rows(_rows), cols(_cols)
{
	init(rows, cols);
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols)
{
	data = new double* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		data[i] = new double[cols];
		for (size_t j = 0; j < cols; j++)
		{
			data[i][j] = other.data[i][j];
		}
	}
}

Matrix::Matrix(double** _data, size_t _rows, size_t _cols) : rows(_rows), cols(_cols)
{
	data = new double* [_rows];
	for (size_t i = 0; i < _rows; i++)
	{
		data[i] = new double[_cols];
		for (size_t j = 0; j < _cols; j++)
		{
			data[i][j] = _data[i][j];
		}
	}
}

Matrix::Matrix(const Matrix& a, const Matrix& b)
{
	init(a.rows, b.cols);

	for (size_t i = 0; i < a.rows; i++)
	{
		for (size_t j = 0; j < b.cols; j++)
		{
			for (size_t k = 0; k < b.rows; k++)
			{
				data[i][j] += a.data[i][k] * b.data[k][j];
			}
		}
	}
}

Matrix Matrix::transpose()
{
	Matrix matrix(cols, rows);

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			matrix.data[j][i] = data[i][j];
		}
	}

	return matrix;
}

void Matrix::dispose()
{
	for (size_t i = 0; i < rows; i++)
	{
		if (data[i])
		{
			delete[] data[i];
			data[i] = nullptr;
		}
	}

	if (data)
	{
		delete[] data;
		data = nullptr;
	}
}

Proxy Matrix::operator[](int index)
{
	return Proxy(data[index], cols);
}

Matrix& Matrix::operator+=(const Matrix& rhs)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			data[i][j] += rhs.data[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			data[i][j] -= rhs.data[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator^=(const Matrix& rhs)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			data[i][j] *= rhs.data[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator*=(double value)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			data[i][j] *= value;
		}
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix& rhs)
{
	return Matrix(*this) += rhs;
}

Matrix Matrix::operator-(const Matrix& rhs)
{
	return Matrix(*this) -= rhs;
}

Matrix Matrix::operator^(const Matrix& rhs)
{
	return Matrix(*this) ^= rhs;
}

Matrix Matrix::operator*(const Matrix& rhs)
{
	return Matrix(*this, rhs);
}

Matrix Matrix::operator*(double value)
{
	return Matrix(*this) *= value;
}

