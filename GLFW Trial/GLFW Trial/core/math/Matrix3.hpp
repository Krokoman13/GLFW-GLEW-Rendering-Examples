#pragma once
#include "../Math/Matrix.hpp"

struct Matrix3 : public Matrix
{
public:
	Matrix3();
	explicit Matrix3(const Matrix& other);

	void SetXPos(const float a_x);
	void SetYPos(const float a_y);
	Vec2 GetPos() const;
	
	float GetXScale() const;
	float GetYScale() const;
	Vec2 GetScale() const;

	Vec2 GetRotVec() const;
	float GetRotRad() const;

	static Matrix3 TranslateMatrix(const Vec2& a_pos);
	static Matrix3 ScalingMatrix(const Vec2& a_scale);
	static Matrix3 RotationMatrix(const Vec2& a_rotation);
	static Matrix3 RotationMatrix(const float a_radians);

	void Translate(const Vec2& a_pos);
	void Scale(const Vec2& a_scale);
	void Rotate(const float a_radians);

	Matrix3 operator=(const Matrix& a_other);
};

