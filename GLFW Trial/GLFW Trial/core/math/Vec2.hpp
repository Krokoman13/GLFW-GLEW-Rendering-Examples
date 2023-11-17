#pragma once
#include <iostream>

/// <summary>
/// 2D Vector. Meant for 2D physics calculations.
/// </summary>
struct Vec2 
{
	float x;
	float y;

	Vec2() : Vec2(0.0f, 0.0f) {}
	Vec2(const float pX, const  float pY) : x(pX), y(pY) {}
	Vec2(const Vec2& pOther) = default;
	~Vec2() = default;

	Vec2& operator=(const Vec2& pOther) = default;

	Vec2 operator+(const Vec2& pOther) const;
	Vec2& operator+=(const Vec2& pOther);

	Vec2 operator-(const Vec2& pOther) const;
	friend Vec2 operator-(const Vec2& pOther);
	Vec2& operator-=(const Vec2& pOther);

	Vec2 operator*(const float pScalar) const;
	friend Vec2 operator*(const float pScalar, const Vec2& vec);
	Vec2& operator*=(const float pScalar);

	Vec2 operator/(const float pScalar) const;
	friend Vec2 operator/(const float pScalar, const Vec2& vec);
	Vec2& operator/=(const float pScalar);

	bool operator==(const Vec2& pOther) const;
	bool operator!=(const Vec2& pOther) const;

	float Length() const;
	float LengthSquared() const;
	Vec2 Normalized() const;
	void Normalize();
	Vec2 Normal() const;
	void SetLength(float pLength);
	void Set(float pX, float pY);
	
	static Vec2 LinInt(const Vec2& pLeft, const Vec2& pRight, const float pInterpolater);
	
	static float Deg2Rad(const float pDegree);
	static float Rad2Deg(const float pRadians);
	
	static Vec2 GetUnitVectorDeg(const float pDegree);
	static Vec2 GetUnitVectorRad(const float pRadians);

	void SetAngleDegrees(const float pDegree);
	void SetAngleRadians(const float pRadians);
	float GetAngleRadians() const;
	float GetAngleDegrees() const;

	Vec2 RotatedRadians(const float pRadians) const;
	void RotateRadians(const float pRadians);
	Vec2 RotatedDegrees(const float pDegree) const;
	void RotateDegrees(const float pDegree);
	void RotateAroundDegrees(const float pDegree, Vec2 pAround);
	void RotateAroundRadians(const float pRadians, Vec2 pAround);

	void RotateTowardsDegrees(const float pTargetDegrees, const float pStepDegrees);

	float Dot( const Vec2& pOther) const;
	Vec2 Project(const Vec2& pOther) const;
	Vec2 Reflected(const Vec2& pNormal, const float pBounciness = 1) const;
	void Reflect( const Vec2& pNormal, const float pBounciness = 1);
	
	static float VectorDotProduct( const Vec2& a,  const Vec2& b);

	static Vec2 Zero();
	static Vec2 Up();
	static Vec2 Down();
	static Vec2 Left();
	static Vec2 Right();

	friend std::ostream& operator << (std::ostream& pOut, const Vec2& pVec);

private:
	static float normalizeDeg(const float pDegree);
};
