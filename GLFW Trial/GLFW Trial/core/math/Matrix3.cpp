#include "Matrix3.hpp"
#include "Vec2.hpp"

Matrix3::Matrix3(): Matrix(3, 3)
{
	*this = Matrix::Identity(3);
}

Matrix3::Matrix3(const Matrix& pOther) : Matrix(3, 3)
{
	if (pOther.GetColumns() != 3 || pOther.GetRows() != 3) throw std::out_of_range("Invalid size Matrix");
	SetArray(pOther.GetArray());
}

Vec2 Matrix3::GetPos() const
{
	return Vec2(Get(0,2), Get(1, 2));
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

Matrix3 Matrix3::TranslateMatrix(const Vec2& pPos)
{
	Matrix3 out;
	out.Set(0, 2, pPos.x);
	out.Set(1, 2, pPos.y);
	return out;
}

Matrix3 Matrix3::ScalingMatrix(const Vec2& pScale)
{
	Matrix3 out;
	out.Set(0, 0, pScale.x);
	out.Set(1, 0, 0);
	out.Set(0, 1, 0);
	out.Set(1, 1, pScale.y);
	return out;
}

Matrix3 Matrix3::RotationMatrix(const Vec2& pRotVector)
{
	Vec2 rotVecNorm = pRotVector.Normalized();

	Matrix3 out;
	out.Set(0, 0, rotVecNorm.x);
	out.Set(1, 0, rotVecNorm.y);

	const Vec2 yAxis = rotVecNorm.RotatedDegrees(90.0f);
	out.Set(0, 1, yAxis.x);
	out.Set(1, 1, yAxis.y);
	return out;
}

Matrix3 Matrix3::RotationMatrix(float pRadians)
{
	return RotationMatrix(Vec2::GetUnitVectorRad(pRadians));
}

void Matrix3::Translate(const Vec2& pPos)
{
	(*this) = (*this) * TranslateMatrix(pPos);
}

void Matrix3::Scale(const Vec2& pScale)
{
	(*this) = (*this) * ScalingMatrix(pScale);
}

void Matrix3::Rotate(const float pRadians)
{
	(*this) = (*this) * RotationMatrix(pRadians);
}

Matrix3 Matrix3::operator=(const Matrix& pOther)
{
	if (pOther.GetColumns() != 3 || pOther.GetRows() != 3) throw std::out_of_range("Invalid size Matrix");

	for (unsigned int y = 0; y < pOther.GetRows(); y++)
	{
		for (unsigned int x = 0; x < pOther.GetColumns(); x++)
		{
			this->Set(x, y, pOther.Get(x, y));
		}
	}

	return *this;
}

float* Matrix3::Data() const
{
	float outp[] =
	{
		Get(0, 0), Get(1, 0), Get(1, 0),
		Get(0, 1), Get(1, 1), Get(1, 1),
		Get(0, 2), Get(1, 2), Get(1, 2)
	};

	return outp;
}
