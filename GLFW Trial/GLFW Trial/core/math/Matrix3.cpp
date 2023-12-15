#include "Matrix3.hpp"
#include "Vec2.hpp"

Matrix3::Matrix3(): Matrix(3, 3)
{
	*this = Matrix::Identity(3);
}

Matrix3::Matrix3(const Matrix& a_other) : Matrix(3, 3)
{
	if (a_other.GetColumns() != 3 || a_other.GetRows() != 3) throw std::out_of_range("Invalid size Matrix");
	SetArray(a_other.GetArray());
}

void Matrix3::SetXPos(const float a_x)
{
	Set(2, 0, a_x);
}

void Matrix3::SetYPos(const float a_y)
{
	Set(2, 1, a_y);
}

Vec2 Matrix3::GetPos() const
{
	return Vec2(Get(2, 0), Get(2, 1));
}

float Matrix3::GetXScale() const
{
	return Vec2(Get(0, 0), Get(1, 0)).Length();		//Gets the xAxis and returns the length
}

float Matrix3::GetYScale() const
{
	return Vec2(Get(0, 1), Get(1, 1)).Length();		//Gets the yAxis and returns the length
}

Vec2 Matrix3::GetScale() const
{
	return Vec2(GetXScale(), GetYScale());
}

Vec2 Matrix3::GetRotVec() const
{
	Vec2 xAxis = Vec2(Get(0, 0), Get(1, 0));
	return xAxis.Normalized();
}

float Matrix3::GetRotRad() const
{
	return GetRotVec().GetAngleRadians();
}

Matrix3 Matrix3::TranslateMatrix(const Vec2& a_pos)
{
	Matrix3 out;
	out.SetXPos(a_pos.x);
	out.SetYPos(a_pos.y);
	return out;
}

Matrix3 Matrix3::ScalingMatrix(const Vec2& a_scale)
{
	Matrix3 out;
	out.Set(0, 0, a_scale.x);
	out.Set(1, 0, 0);
	out.Set(0, 1, 0);
	out.Set(1, 1, a_scale.y);
	return out;
}

Matrix3 Matrix3::RotationMatrix(const Vec2& a_rotVector)
{
	Vec2 rotVecNorm = a_rotVector.Normalized();

	Matrix3 out;
	out.Set(0, 0, rotVecNorm.x);
	out.Set(1, 0, rotVecNorm.y);

	const Vec2 yAxis = rotVecNorm.RotatedDegrees(90.0f);
	out.Set(0, 1, yAxis.x);
	out.Set(1, 1, yAxis.y);
	return out;
}

Matrix3 Matrix3::RotationMatrix(float a_radians)
{
	Matrix3 out;
	out.Set(0, 0, cos(a_radians));
	out.Set(1, 0, sin(a_radians));
	out.Set(0, 1, -sin(a_radians));
	out.Set(1, 1, cos(a_radians));
	return out;
}

void Matrix3::Translate(const Vec2& a_pos)
{
	(*this) = (*this) * TranslateMatrix(a_pos);
}

void Matrix3::Scale(const Vec2& a_scale)
{
	(*this) = (*this) * ScalingMatrix(a_scale);
}

void Matrix3::Rotate(const float a_radians)
{
	(*this) = (*this) * RotationMatrix(a_radians);
}

Matrix3 Matrix3::operator=(const Matrix& a_other)
{
	if (a_other.GetColumns() != 3 || a_other.GetRows() != 3) throw std::out_of_range("Invalid size Matrix");

	for (unsigned int y = 0; y < a_other.GetRows(); y++)
	{
		for (unsigned int x = 0; x < a_other.GetColumns(); x++)
		{
			this->Set(x, y, a_other.Get(x, y));
		}
	}

	return *this;
}
