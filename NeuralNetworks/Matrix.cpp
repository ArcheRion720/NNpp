#include "Matrix.h"

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
		memset(data[i], 0, cols * sizeof(double));
	}
}

void Matrix::random(size_t _rows, size_t _cols, double min, double max)
{
	static std::default_random_engine rng(std::random_device{}());
	std::uniform_real_distribution<double> dist(min, max);

	disposeData();
	allocData(_rows, _cols);

	for (size_t i = 0; i < _rows; i++)
	{
		data[i] = new double[_cols];
		for (size_t j = 0; j < _cols; j++)
		{
			data[i][j] = dist(rng);
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

size_t Matrix::length()
{
	return rows * cols;
}

void Matrix::readFromArray(double* buffer)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			data[i][j] = buffer[i * cols + j];
		}
	}
}

void Matrix::readImage(unsigned char* img, int width, int height, int imgWidth, int imgHeight, int x, int y)
{
	disposeData();
	initEmpty(static_cast<size_t>(width) * height, 1);

	unsigned char* ptr = img + (x * width + y * height * imgHeight);

	int index = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			data[index++][0] = ptr[j] / 255.0;
		}
		ptr += imgWidth;
	}
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
	if (this == nullptr)
		return;

	if (data != nullptr)
	{
		for (size_t i = 0; i < rows; i++)
			delete[] data[i];

		delete[] data;
		data = nullptr;
	}
}

inline void Matrix::copyData(const Matrix& matrix)
{
	initEmpty(matrix.rows, matrix.cols);

	for (size_t i = 0; i < rows; i++)
	{
		memcpy(data[i], matrix.data[i], cols * sizeof(double));
	}
}