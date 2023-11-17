#pragma once
#include "DynamicFloatArray.hpp"
#include <iostream>

struct Vec2;

struct  Matrix
{
private:
	unsigned int m_rowCount;
	unsigned int m_columnCount;
	DynamicFloatArray m_elements;

public:
	Matrix(const unsigned int a_rows, const unsigned int a_columns);
	Matrix(const Matrix& a_other);
	Matrix(const Vec2& a_vector);
	~Matrix();

	inline const unsigned int GetColumns() const;
	inline const unsigned int GetRows() const;

	static Matrix Identity(const unsigned int a_size);

	float Get(const unsigned int a_columnIndex, const unsigned int a_rowIndex) const;
	void Set(const unsigned int a_columnIndex, const unsigned int a_rowIndex, const float a_value);

	void Fill(const float a_value);

	Matrix Transposed() const;
	void Transpose();

	void SetArray(const DynamicFloatArray &a_array);
	const DynamicFloatArray& GetArray() const;

	void SwapRows(const unsigned int a_rowAIndex, const unsigned int a_rowBIndex);
	Matrix SubMatrix(const unsigned int a_ExRow, const unsigned int a_ExColumn) const;
	static Matrix ConcatenateVertically(const Matrix& a_topMatrix, const Matrix& a_bottemMatrix);
	static Matrix ConcatenateHorizontally(const Matrix& a_leftMatrix, const Matrix& a_rightMatrix);
	float Determinant() const;
	Matrix Inverse() const;

	Matrix operator=(const Matrix& a_other);

	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& os, const Matrix& dt);
};

Matrix operator*(const Matrix& left, const Matrix& right);
Matrix operator*=(Matrix& left, const Matrix& right);
