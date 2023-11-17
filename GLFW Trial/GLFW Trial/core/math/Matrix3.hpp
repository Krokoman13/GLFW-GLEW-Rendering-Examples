#pragma once
#include "../Math/Matrix.hpp"

struct Matrix3 : public Matrix
{
public:
	Matrix3();
	explicit Matrix3(const Matrix& other);

	Vec2 GetPos() const;

	float GetXScale() const;
	float GetYScale() const;
	Vec2 GetScale() const;

	Vec2 GetRotVec() const;
	float GetRotRad() const;

	static Matrix3 TranslateMatrix(const Vec2& pPos);
	static Matrix3 ScalingMatrix(const Vec2& pScale);
	static Matrix3 RotationMatrix(const Vec2& pRotation);
	static Matrix3 RotationMatrix(const float pRadians);

	void Translate(const Vec2& pPos);
	void Scale(const Vec2& pScale);
	void Rotate(const float pRadians);

	Matrix3 operator=(const Matrix& other);
	float* Data() const;
};

