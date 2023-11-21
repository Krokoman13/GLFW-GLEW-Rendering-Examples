#include <string>
#include "Matrix.hpp"
#include "Vec2.hpp"

Matrix::Matrix(const unsigned int a_rows, const unsigned int a_columns) : m_elements(a_rows * a_columns)
{
	m_rowCount = a_rows;
	m_columnCount = a_columns;
}

const unsigned int Matrix::GetColumns() const
{
	return m_columnCount;
}

const unsigned int Matrix::GetRows() const
{
	return m_rowCount;
}


Matrix::Matrix(const Matrix& a_other) : Matrix(a_other.m_columnCount, a_other.m_rowCount)
{
	if (this == &a_other) return;

	for (unsigned int y = 0; y < a_other.m_rowCount; y++)
	{
		for (unsigned int x = 0; x < a_other.m_columnCount; x++)
		{
			Set(x, y, a_other.Get(x, y));
		}
	}
}

Matrix::Matrix(const Vec2& a_vector) : Matrix(1, 2)
{
	Set(0, 0, a_vector.x);
	Set(0, 1, a_vector.y);
}

Matrix::~Matrix()
{
}

Matrix Matrix::Identity(const unsigned int a_size)
{
	Matrix out(a_size, a_size);

	for (unsigned int i = 0; i < a_size; i++) out.Set(i,i, 1);

	return out;
}

float Matrix::Get(const unsigned int a_columnIndex, const unsigned int a_rowIndex) const
{
	if (a_rowIndex >= m_rowCount || a_columnIndex >= m_columnCount) throw std::out_of_range("Index is out of range");
	unsigned int i = a_rowIndex + a_columnIndex * m_rowCount;
	return m_elements[i];
}

void Matrix::Set(const unsigned int a_columnIndex, const unsigned int a_rowIndex, const float a_value)
{
	if (a_rowIndex >= m_rowCount || a_columnIndex >= m_columnCount) throw std::out_of_range("Index is out of range");
	unsigned int i = a_rowIndex + a_columnIndex * m_rowCount;
	m_elements[i] = a_value;
}

void Matrix::Fill(const float a_value)
{
	for (unsigned int i = 0; i < m_columnCount * m_rowCount; i++)
	{
		m_elements[i] = a_value;
	}
}

Matrix Matrix::Transposed() const
{
	Matrix transposed = Matrix(m_columnCount, m_rowCount);

	for (unsigned int y = 0; y < transposed.m_rowCount; y++)
	{
		for (unsigned int x = 0; x < transposed.m_columnCount; x++)
		{
			transposed.Set(x, y, Get(y, x));
		}
	}

	return transposed;
}

void Matrix::Transpose()
{
	(*this) = this->Transposed();
}

void Matrix::SetArray(const DynamicFloatArray& a_array)
{
	if (this->GetColumns() * this->GetRows() != a_array.GetSize()) throw std::out_of_range("Invalid size Array");
	m_elements = a_array;
}

const DynamicFloatArray& Matrix::GetArray() const
{
	return m_elements;
}

void Matrix::SwapRows(const unsigned int a_rowAIndex, const unsigned int a_rowBIndex)
{
	if (a_rowAIndex >= m_rowCount || a_rowBIndex >= m_rowCount) throw std::out_of_range("Matrix: Row index out of range.");
	if (a_rowAIndex == a_rowBIndex) return;

	for (unsigned int i = 0; i < m_columnCount; i++)
	{
		float temp = Get(i, a_rowAIndex);
		Set(i, a_rowAIndex, Get(i, a_rowBIndex));
		Set(i, a_rowAIndex, temp);
	}
}


Matrix Matrix::SubMatrix(const unsigned int a_ExRow, const unsigned int a_ExColumn) const
{
	const unsigned int size = GetRows();
	Matrix submatrix(size - 1, size - 1);

	unsigned int subRow = 0;
	unsigned int subColumn = 0;

	for (unsigned int row = 0; row < size; row++)
	{
		if (row == a_ExRow) continue;

		subColumn = 0;

		for (unsigned int column = 0; column < size; column++)
		{
			if (column == a_ExColumn) continue;

			submatrix.Set(subRow, subColumn, Get(row, column));
			subColumn++;
		}

		subRow++;
	}

	return submatrix;
}

Matrix Matrix::ConcatenateVertically(const Matrix& a_topMatrix, const Matrix& a_bottemMatrix)
{
	if (a_topMatrix.m_columnCount != a_bottemMatrix.m_columnCount)
	{
		throw std::invalid_argument("Matrix: Number of columns must be the same for concatenation.");
	}

	Matrix concatenatedMatrix(a_topMatrix.m_rowCount + a_bottemMatrix.m_rowCount, a_topMatrix.m_columnCount);

	for (unsigned int y = 0; y < a_topMatrix.m_rowCount; y++)
	{
		for (unsigned int x = 0; x < a_topMatrix.m_columnCount; x++)
		{
			concatenatedMatrix.Set(x, y, a_topMatrix.Get(x, y));
		}
	}

	for (unsigned int y = 0; y < a_bottemMatrix.m_rowCount; y++)
	{
		for (unsigned int x = 0; x < a_bottemMatrix.m_columnCount; x++)
		{
			concatenatedMatrix.Set(x, y + a_topMatrix.m_rowCount, a_bottemMatrix.Get(x, y));
		}
	}

	return concatenatedMatrix;
}

Matrix Matrix::ConcatenateHorizontally(const Matrix& a_leftMatrix, const Matrix& a_rightMatrix)
{
	if (a_leftMatrix.m_rowCount != a_rightMatrix.m_rowCount)
	{
		throw std::invalid_argument("Matrix: Number of columns must be the same for concatenation.");
	}

	Matrix concatenatedMatrix(a_leftMatrix.m_rowCount, a_leftMatrix.m_columnCount + a_rightMatrix.m_columnCount);

	for (unsigned int y = 0; y < a_leftMatrix.m_rowCount; y++)
	{
		for (unsigned int x = 0; x < a_leftMatrix.m_columnCount; x++)
		{
			concatenatedMatrix.Set(x, y, a_leftMatrix.Get(x, y));
		}
	}

	for (unsigned int y = 0; y < a_rightMatrix.m_rowCount; y++)
	{
		for (unsigned int x = 0; x < a_rightMatrix.m_columnCount; x++)
		{
			concatenatedMatrix.Set(x + a_leftMatrix.m_columnCount, y, a_rightMatrix.Get(x, y));
		}
	}

	return concatenatedMatrix;
}

float Matrix::Determinant() const
{
	if (m_rowCount != m_columnCount) throw std::runtime_error("Matrix: Determinant does not exist, matrix is not square.");

	unsigned int n = m_rowCount;

	if (n == 1) return Get(0, 0);
	if (n == 2)	return Get(0, 0) * Get(1, 1) - Get(0, 1) * Get(1, 0);

	const unsigned int size = GetRows();

	if (size == 1)
		return Get(0, 0);

	float determinant = 0.0f;
	Matrix submatrix(size - 1, size - 1);

	for (unsigned int i = 0; i < size; i++)
	{
		submatrix = SubMatrix(0, i);
		determinant += (i % 2 == 0 ? 1.0f : -1.0f) * Get(0, i) * submatrix.Determinant();
	}

	return determinant;
}

Matrix Matrix::Inverse() const
{
	if (m_rowCount != m_columnCount) throw std::runtime_error("Matrix: Inverse does not exist, matrix is not square.");

	float determinant = Determinant();

	if (determinant == 0)
	{
		throw std::logic_error("Matrix is not invertible.");
	}

	Matrix outp(m_rowCount, m_columnCount);

	for (unsigned int y = 0; y < m_rowCount; y++)
	{
		for (unsigned int x = 0; x < m_columnCount; x++)
		{
			Matrix sub = SubMatrix(x, y);
			float cofactor = sub.Determinant();
			cofactor *= ((x + y) % 2 == 0) ? 1 : -1;
			outp.Set(y, x, cofactor / determinant);
		}
	}

	return outp;
}
	

Matrix Matrix::operator=(const Matrix& a_other)
{
	if (this == &a_other) return *this;

	m_columnCount = a_other.m_columnCount;
	m_rowCount = a_other.m_rowCount;
	m_elements = a_other.m_elements;

	return *this;
}

bool Matrix::operator==(const Matrix& a_other)
{
	if (GetColumns() != a_other.GetColumns() || GetRows() != a_other.GetRows()) return false;

	return m_elements == a_other.m_elements;
}

bool Matrix::operator!=(const Matrix& a_other)
{
	return !(*this == a_other);
}

std::string Matrix::ToString() const
{
	std::string outp;
	for (unsigned int y = 0; y < GetRows(); y++)
	{
		outp += '[';
		unsigned int x = 0;
		while (true)
		{
			outp += std::to_string(Get(x, y));
			if (x >= GetColumns() - 1) break;
			outp += ',';
			x++;
		}
		outp += "]\n";
	}

	return outp;
}

std::ostream& operator<<(std::ostream& os, const Matrix& dt)
{
	os << dt.ToString();
	return os;
}

Matrix operator*(const Matrix& left, const Matrix& right)
{
	if (right.GetColumns() != left.GetRows())
	{
		throw std::invalid_argument("Invalid size of Matrices to multiply");
	}

	Matrix out(left.GetColumns(), right.GetRows());

	for (unsigned int i = 0; i < left.GetColumns(); i++) 
	{
		for (unsigned int j = 0; j < right.GetRows(); j++) 
		{
			float value = 0;

			for (unsigned int k = 0; k < right.GetColumns(); k++)
			{
				value += right.Get(i,k) * left.Get(k,j);
			}

			out.Set(i, j, value);
		}

	}

	return out;
}

Matrix operator*=(Matrix& left, const Matrix& right)
{
	left = left * right;
	return left;
}
