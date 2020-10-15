#include "Matrix.h"
#include <time.h>

double Matrix::randNum(double min, double max)
{
	static std::default_random_engine rng(std::random_device{}());
	std::uniform_real_distribution<double> dist(min, max);

	return dist(rng);
}

void Matrix::initEmpty(size_t _rows, size_t _cols)
{
	allocData(_rows, _cols);

	for (size_t i = 0; i < rows; i++)
		data[i] = new double[cols];
}

void Matrix::initFill(size_t _rows, size_t _cols, double value)
{
	allocData(_rows, _cols);

	for (size_t i = 0; i < rows; i++)
	{
		data[i] = new double[cols];
		for (size_t j = 0; j < cols; j++)
		{
			data[i][j] = value;
		}
	}
}

void Matrix::initRandom(size_t _rows, size_t _cols, double min, double max)
{
	disposeData();
	allocData(_rows, _cols);

	for (size_t i = 0; i < _rows; i++)
	{
		data[i] = new double[_cols];
		for (size_t j = 0; j < _cols; j++)
		{
			data[i][j] = randNum(min, max);
		}
	}
}

Matrix::Matrix() : rows(0), cols(0), data(nullptr)
{}

Matrix::Matrix(size_t _rows, size_t _cols)
{
	initFill(_rows, _cols, 0.0);
}

Matrix::Matrix(const Matrix& matrix)
{
	copyData(matrix);
}

Matrix::~Matrix()
{
	disposeData();
}

Proxy Matrix::operator[](size_t index) const
{
	return Proxy(data[index], cols);
}

Matrix& Matrix::operator=(const Matrix& matrix)
{
	if (this == &matrix)
		return *this;

	disposeData();
	copyData(matrix);

	return *this;
}

Matrix& Matrix::operator+=(const Matrix& rhs)
{
	if (rows != rhs.rows || cols != rhs.cols)
		throw Matrix::IncompatibleMatrixException();

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			data[i][j] += rhs[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs)
{
	if (rows != rhs.rows || cols != rhs.cols)
		throw Matrix::IncompatibleMatrixException();

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			data[i][j] -= rhs[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator^=(const Matrix& rhs)
{
	if (rows != rhs.rows || cols != rhs.cols)
		throw Matrix::IncompatibleMatrixException();

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			data[i][j] *= rhs[i][j];
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
	if (cols != rhs.rows)
		throw Matrix::IncompatibleMatrixException();

	Matrix result(rows, rhs.cols);

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < rhs.cols; j++)
		{
			for (size_t k = 0; k < rhs.rows; k++)
			{
				result[i][j] += data[i][k] * rhs.data[k][j];
			}
		}
	}

	return result;
}

Matrix Matrix::operator*(double value)
{
	return Matrix(*this) *= value;
}

Matrix Matrix::operator~()
{
	Matrix result(cols, rows);

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			result[j][i] = data[i][j];
		}
	}

	return result;
}

void Matrix::callOnElements(callback _call)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			data[i][j] = _call(data[i][j]);
		}
	}
}

inline void Matrix::allocData(size_t _rows, size_t _cols)
{
	rows = _rows;
	cols = _cols;

	data = new double* [rows];
}

inline void Matrix::disposeData()
{
	if (data != nullptr)
	{
		for (size_t i = 0; i < rows; i++)
			delete[] data[i];

		delete data;
		data = nullptr;
	}
}

inline void Matrix::copyData(const Matrix& matrix)
{
	initEmpty(matrix.rows, matrix.cols);

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			data[i][j] = matrix[i][j];
		}
	}
}

//
//double Matrix::randNum(double min, double max)
//{
//	static std::default_random_engine rng(std::random_device{}());
//	std::uniform_real_distribution<double> dist(min, max);
//
//	return dist(rng);
//}
//
//void Matrix::init(size_t _rows, size_t _cols)
//{
//	rows = _rows;
//	cols = _cols;
//
//	data = new double* [_rows];
//	for (size_t i = 0; i < _rows; i++)
//	{
//		data[i] = new double[_cols];
//		for (size_t j = 0; j < _cols; j++)
//		{
//			data[i][j] = 0;
//		}
//	}
//}
//
//void Matrix::initRandom(size_t _rows, size_t _cols, double min, double max)
//{
//	rows = _rows;
//	cols = _cols;
//
//	data = new double* [_rows];
//	for (size_t i = 0; i < rows; i++)
//	{
//		data[i] = new double[_cols];
//		for (size_t j = 0; j < cols; j++)
//		{
//			data[i][j] = randNum(min, max);
//		}
//	}
//}
//
//Matrix::Matrix() : rows(0), cols(0), data(nullptr)
//{ }
//
//Matrix::Matrix(size_t _rows, size_t _cols) : rows(_rows), cols(_cols)
//{
//	init(rows, cols);
//}
//
//Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols)
//{
//	data = new double* [rows];
//	for (size_t i = 0; i < rows; i++)
//	{
//		data[i] = new double[cols];
//		for (size_t j = 0; j < cols; j++)
//		{
//			data[i][j] = other.data[i][j];
//		}
//	}
//}
//
//Matrix::Matrix(double** _data, size_t _rows, size_t _cols) : rows(_rows), cols(_cols)
//{
//	data = new double* [_rows];
//	for (size_t i = 0; i < _rows; i++)
//	{
//		data[i] = new double[_cols];
//		for (size_t j = 0; j < _cols; j++)
//		{
//			data[i][j] = _data[i][j];
//		}
//	}
//}
//
//Matrix::Matrix(const Matrix& a, const Matrix& b)
//{
//	init(a.rows, b.cols);
//
//	for (size_t i = 0; i < a.rows; i++)
//	{
//		for (size_t j = 0; j < b.cols; j++)
//		{
//			for (size_t k = 0; k < b.rows; k++)
//			{
//				data[i][j] += a.data[i][k] * b.data[k][j];
//			}
//		}
//	}
//}
//
//Matrix Matrix::transpose()
//{
//	Matrix matrix(cols, rows);
//
//	for (size_t i = 0; i < rows; i++)
//	{
//		for (size_t j = 0; j < cols; j++)
//		{
//			matrix.data[j][i] = data[i][j];
//		}
//	}
//
//	return matrix;
//}
//
//void Matrix::dispose()
//{
//	for (size_t i = 0; i < rows; i++)
//	{
//		if (data[i])
//		{
//			delete[] data[i];
//			data[i] = nullptr;
//		}
//	}
//
//	if (data)
//	{
//		delete[] data;
//		data = nullptr;
//	}
//}
//
//Proxy Matrix::operator[](int index)
//{
//	return Proxy(data[index], cols);
//}
//
//Matrix& Matrix::operator+=(const Matrix& rhs)
//{
//	for (size_t i = 0; i < rows; i++)
//	{
//		for (size_t j = 0; j < cols; j++)
//		{
//			data[i][j] += rhs.data[i][j];
//		}
//	}
//
//	return *this;
//}
//
//Matrix& Matrix::operator-=(const Matrix& rhs)
//{
//	for (size_t i = 0; i < rows; i++)
//	{
//		for (size_t j = 0; j < cols; j++)
//		{
//			data[i][j] -= rhs.data[i][j];
//		}
//	}
//
//	return *this;
//}
//
//Matrix& Matrix::operator^=(const Matrix& rhs)
//{
//	for (size_t i = 0; i < rows; i++)
//	{
//		for (size_t j = 0; j < cols; j++)
//		{
//			data[i][j] *= rhs.data[i][j];
//		}
//	}
//
//	return *this;
//}
//
//Matrix& Matrix::operator*=(double value)
//{
//	for (size_t i = 0; i < rows; i++)
//	{
//		for (size_t j = 0; j < cols; j++)
//		{
//			data[i][j] *= value;
//		}
//	}
//	return *this;
//}
//
//Matrix Matrix::operator+(const Matrix& rhs)
//{
//	return Matrix(*this) += rhs;
//}
//
//Matrix Matrix::operator-(const Matrix& rhs)
//{
//	return Matrix(*this) -= rhs;
//}
//
//Matrix Matrix::operator^(const Matrix& rhs)
//{
//	return Matrix(*this) ^= rhs;
//}
//
//Matrix Matrix::operator*(const Matrix& rhs)
//{
//	return Matrix(*this, rhs);
//}
//
//Matrix Matrix::operator*(double value)
//{
//	return Matrix(*this) *= value;
//}
//
