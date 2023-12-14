#pragma once
#include "../Core/Math/Matrix3.hpp"
#include "../Core/Math/Vec2.hpp"

//struct Vec2;

class Transform
{
public:
	Transform();
	Transform(const Vec2& a_localPosition);
	Transform(const float a_x, const float a_y);
	virtual ~Transform() = default;

	Matrix3 identity;

protected:
	Transform* m_parent = nullptr;

public:
	void SetParent(Transform* pParent);

	void SetLocalPosition(const Vec2& a_pos);
	void SetLocalPosition(const float pX, const float a_y);
	Vec2 GetLocalPosition() const;

	void GlobalTranslate(const Vec2& a_translation);
	void SetGlobalPosition(const Vec2& a_pos);
	void SetGlobalPosition(const float a_x, const float a_y);
	Vec2 GetGlobalPosition() const;

	void SetLocalRotation(const float a_radians);
	float GetLocalRotationRad() const;

	void SetGlobalRotation(const float a_radians);
	float GetGlobalRotationRad()const;

	void SetLocalScale(Vec2 a_scale);
	void SetLocalScale(const float a_uniformScale);
	float GetLocalXScale() const;
	float GetLocalYScale() const;
	Vec2 GetLocalScale() const;

	void SetGlobalScale(const Vec2& a_scale);
	void SetGlobalScale(const float a_uniformScale);
	float GetGlobalXScale() const;
	float GetGlobalYScale() const;
	Vec2 GetGlobalScale() const;

	Matrix3 GetGlobalMatrix() const;
	void SetGlobalMatrix(const Matrix3& a_matrix);
	
	Matrix3 InverseModificationMatrix() const;
};