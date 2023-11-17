#include <cmath>
#include "Vec2.hpp"
#include "Matrix.hpp"
#define M_PI          3.141592653589793238462643383279502884L /* pi */

//------------------------------------------------------------------------------------------------------------------------
//														+ operator
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Returns the result of adding two vectors(without modifying either of them)
/// </summary>
Vec2 Vec2::operator+(const Vec2& pOther) const
{
	return Vec2(x + pOther.x, y + pOther.y);
}

Vec2& Vec2::operator+=(const Vec2& pOther)
{
	x += pOther.x;
	y += pOther.y;
	return *this;
}

//------------------------------------------------------------------------------------------------------------------------
//														- operator
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Returns the result of subtracting two vectors(without modifying either of them)
/// </summary>
Vec2 Vec2::operator-(const Vec2& pOther) const
{
	return Vec2(x - pOther.x, y - pOther.y);
}

Vec2 operator-(const Vec2& pOther)
{
	return Vec2(-pOther.x, -pOther.y);
}

Vec2& Vec2::operator-=(const Vec2& pOther)
{
	x -= pOther.x;
	y -= pOther.y;
	return *this;
}

//------------------------------------------------------------------------------------------------------------------------
//														* operator
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Returns the result of multiplying a vector by a float(without modifying either of them)
/// </summary>
Vec2 Vec2::operator*(const float pScalar) const
{
	return Vec2(x * pScalar, y * pScalar);
}

Vec2 operator*(const float pScalar, const Vec2& pVec)
{
	return pVec * pScalar;
}

Vec2& Vec2::operator*=(const float pScalar)
{
	*this = *this * pScalar;
	return *this;
}

//------------------------------------------------------------------------------------------------------------------------
//														/ operator
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Returns the result of deviding a vector by a float(without modifying either of them)
/// </summary>

Vec2 Vec2::operator/(const float pScalar) const
{
	// Check for division by zero
	if (pScalar == 0.0f)
	{
		std::cerr << "Error: Division by zero in Vec2::operator/!" << std::endl;
		return *this;
	}

	return Vec2(x / pScalar, y / pScalar);
}

Vec2 operator/(const float pScalar, const Vec2& pVec)
{
	// Check for division by zero
	if (pVec.x == 0.0f || pVec.y == 0.0f)
	{
		std::cerr << "Error: Division by zero in Vec2::operator/!" << std::endl;
		return pVec;
	}

	return Vec2(pScalar / pVec.x, pScalar / pVec.y);
}

Vec2& Vec2::operator/=(const float pScalar)
{
	*this = *this / pScalar;
	return *this;
}

//------------------------------------------------------------------------------------------------------------------------
//														== operator
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Returns a bool that indicates if the two vectors are the same
/// </summary>
bool Vec2::operator==(const Vec2& pOther) const
{
	return (x == pOther.x) && (y == pOther.y);
}

bool Vec2::operator!=(const Vec2& pOther) const
{
	return !(*this == pOther);
}

//------------------------------------------------------------------------------------------------------------------------
//														Length()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Returns the length of the current vector
/// </summary>
float Vec2::Length() const
{
	return sqrt(LengthSquared());     //Using Pythagorean theorem to calculate the length of the vector
}

float Vec2::LengthSquared() const
{
	return x * x + y * y;
}

//------------------------------------------------------------------------------------------------------------------------
//														Normalized()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Returns a normalized version of the current vector without modifying it
/// </summary>
Vec2 Vec2::Normalized() const
{
	const float len = Length();

	if (len == 0.0f) return *this; 
	return *this / len;
}

//------------------------------------------------------------------------------------------------------------------------
//														Normalize()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Normalizes the current vector
/// </summary>
void Vec2::Normalize()
{
	*this = this->Normalized();
}

void Vec2::SetLength(float pLength)
{
	this->Normalize();
	*this *= pLength;
}

//------------------------------------------------------------------------------------------------------------------------
//														SetXY()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Sets the x & y of the current vector to the given two floats
/// </summary>
void Vec2::Set(const float pX, const float pY)
{
	x = pX;
	y = pY;
}

//------------------------------------------------------------------------------------------------------------------------
//														LinInt()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Performs a linear interpolation between two vectors based on the given weighting and returns the result.
/// </summary>
/// <param name='left'>
/// The first vector
/// </param>
/// <param name='right'>
/// The second vector
/// </param>
/// <param name='interpolater'>
/// This number specificifies the percentage of the second(right) vector in the result (If this is 0f: The pLeft vector will be returned. If this is 1f: the pRight one. If 0.5f it is an average between the two)
/// </param>
Vec2 Vec2::LinInt(const Vec2& pLeft,  const Vec2& pRight, const float pInterpolater)
{
	return pLeft + pInterpolater * (pRight - pLeft);
}

//------------------------------------------------------------------------------------------------------------------------
//														Deg2Rad()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Converts the given degrees to radians
/// </summary>
/// <param name='degree'>
/// The input degree value
/// </param>
float Vec2::Deg2Rad(const float pDegree)
{
	return ((float)M_PI / 180.0f) * pDegree;
}

//------------------------------------------------------------------------------------------------------------------------
//														Rad2Deg()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Converts the given radians to degrees
/// </summary>	
/// <param name='radians'>
/// The input radians value
/// </param>
float Vec2::Rad2Deg(const float pRadians)
{
	return (180.0f / (float)M_PI) * pRadians;
}

//------------------------------------------------------------------------------------------------------------------------
//														GetUnitVectorDeg ()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Returns a new vector pointing in the given direction in degrees
/// </summary>
Vec2 Vec2::GetUnitVectorDeg(const float pDegree)
{
	return GetUnitVectorRad(Vec2::Deg2Rad(pDegree));
}

//------------------------------------------------------------------------------------------------------------------------
//														GetUnitVectorRad ()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Returns a new vector pointing in the given direction in pRadians
/// </summary>
Vec2 Vec2::GetUnitVectorRad(const float pRadians)
{
	float pX = cos(pRadians);
	float pY = sin(pRadians);

	return Vec2(pX, pY);
}

//------------------------------------------------------------------------------------------------------------------------
//														SetAngleDegrees ()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Changes the current vector to the given degrees (without changing length)
/// </summary>
void Vec2::SetAngleDegrees(const float pDegree)
{
	SetAngleRadians(Deg2Rad(pDegree));
}

//------------------------------------------------------------------------------------------------------------------------
//														SetAngleRadians ()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Changes the current vector to the given pRadians (without changing length)
/// </summary>
void Vec2::SetAngleRadians(const float pRadians)
{
	Vec2 temp = Vec2::GetUnitVectorRad(pRadians);
	temp.SetLength(this->Length());

	*this = temp;
}

//------------------------------------------------------------------------------------------------------------------------
//														GetAngleRadians ()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Returns a float calculated to be the current angle of the vector in pRadians
/// </summary>
float Vec2::GetAngleRadians() const
{
	return atan2(y, x);
}

//------------------------------------------------------------------------------------------------------------------------
//														GetAngleDegrees ()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Returns a float calculated to be the current angle of the vector in degrees
/// </summary>
float Vec2::GetAngleDegrees() const
{
	return Rad2Deg(GetAngleRadians());
}

//------------------------------------------------------------------------------------------------------------------------
//														RotateRadians ()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Rotate the vector over the given angle in pRadians
/// </summary>
Vec2 Vec2::RotatedRadians(const float pRadians) const
{
	const float pX = x * cos(pRadians) - y * sin(pRadians);
	const float pY = x * sin(pRadians) + y * cos(pRadians);

	return Vec2(pX, pY);
}

void Vec2::RotateRadians(const float pRadians)
{
	*this = RotatedRadians(pRadians);
}

//------------------------------------------------------------------------------------------------------------------------
//														RotateDegrees ()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Rotate the vector over the given angle in degrees
/// </summary>

Vec2 Vec2::RotatedDegrees(const float pDegrees) const
{
	return RotatedRadians(Deg2Rad(pDegrees));
}

void Vec2::RotateDegrees(const float pDegrees)
{
	RotateRadians(Deg2Rad(pDegrees));
}

//------------------------------------------------------------------------------------------------------------------------
//														RotateAroundDegrees ()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Rotate the vector around the given point over the given angle in degrees
/// </summary>
void Vec2::RotateAroundDegrees(const float pDegrees, const  Vec2 pAround)
{
	RotateAroundRadians(Deg2Rad(pDegrees), pAround);
}

//------------------------------------------------------------------------------------------------------------------------
//														RotateAroundRadians ()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Rotate the vector around the given point over the given angle in pRadians
/// </summary>
void Vec2::RotateAroundRadians(const float pRadians, Vec2 pAround)
{
	*this -= pAround;
	RotateRadians(pRadians);
	*this += pAround;
}

//------------------------------------------------------------------------------------------------------------------------
//														normalizeDeg ()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// The entered pDegree value is normalized, the returend value cannot be outside (-180, 180) degrees
/// </summary>
float Vec2::normalizeDeg(float pDegree)
{
	while (pDegree > 180.0f)
	{
		pDegree -= 360.0f;
	}

	while (pDegree < -180.0f)
	{
		pDegree += 360.0f;
	}

	return pDegree;
}

//------------------------------------------------------------------------------------------------------------------------
//														RotateTowardsDegrees()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// The vector will rotate towards the target degrees in given steps
/// </summary>
/// <param name='targetDegrees'>
/// The target degrees for the vector to eventually point too
/// </param>
/// <param name='stepDegrees'>
/// The amount of degrees the vector can turn each time it is called
/// </param>
void Vec2::RotateTowardsDegrees(const float pTargetDegrees, const float pStepDegrees)
{
	//stepDegrees = Mathf.Abs(stepDegrees);
	float diffrence = pTargetDegrees - this->GetAngleDegrees();

	diffrence = normalizeDeg(diffrence);

	if (abs(diffrence) <= pStepDegrees)
	{
		SetAngleDegrees(pTargetDegrees);
	}
	else if (diffrence < 0)
	{
		this->RotateDegrees(-pStepDegrees);
	}
	else if (diffrence > 0)
	{
		this->RotateDegrees(pStepDegrees);
	}
}

//------------------------------------------------------------------------------------------------------------------------
//														Dot()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Will calculate the dot product of a given vector and itself
/// </summary>
float Vec2::Dot( const Vec2& pOther) const
{
	return x * pOther.x + y * pOther.y; ;
}

//------------------------------------------------------------------------------------------------------------------------
//														VectorDotProduct()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Will calculate the dot product of two given vectors
/// </summary>
float Vec2::VectorDotProduct( const Vec2& pA,  const Vec2& pB)
{
	return pA.Dot(pB);
}

//------------------------------------------------------------------------------------------------------------------------
//														Normal()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Returns a normal to this vector
/// </summary>
Vec2 Vec2::Normal() const
{
	Vec2 NormalVec = Vec2(-y, x);
	return NormalVec.Normalized();
}

//------------------------------------------------------------------------------------------------------------------------
//														Project()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Reflects the vector of another vector based on that pOther vector's normal
/// </summary>
Vec2 Vec2::Project(const Vec2& pOther) const
{
	float dot = Dot(pOther);
	float lenSquared = pOther.LengthSquared();

	if (lenSquared != 0.0f)
		return pOther * (dot / lenSquared);
	else
		return Vec2();
}

//------------------------------------------------------------------------------------------------------------------------
//														Reflect()
//------------------------------------------------------------------------------------------------------------------------
/// <summary>
/// Reflects the vector of another vector based on that pOther vector's normal
/// </summary>

Vec2 Vec2::Reflected(const Vec2& pNormal, float pBounciness) const
{
	Vec2 normal = pNormal.Normalized();
	Vec2 outp = *this;
	outp = *this - (1 + pBounciness) * (this->Dot(normal) * normal);
	return outp;
}

void Vec2::Reflect( const Vec2& pNormal, const float pBounciness)
{
	*this = this->Reflected(pNormal, pBounciness) ;
}

Vec2 Vec2::Zero()
{
	return Vec2(0.0f, 0.0f);
}

Vec2 Vec2::Up()
{
	return Vec2(0.0f, 1.0f);
}

Vec2 Vec2::Down()
{
	return Vec2(0.0f, -1.0f);
}

Vec2 Vec2::Left()
{
	return Vec2(-1.0f, 0.0f);
}

Vec2 Vec2::Right()
{
	return Vec2(1.0f, 0.0f);
}

std::ostream& operator<<(std::ostream& pOut, const Vec2& pVec)
{
	pOut << '(' << pVec.x << ',' << pVec.y << ')';
	return pOut;
}