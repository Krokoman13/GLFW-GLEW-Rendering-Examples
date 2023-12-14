#pragma once
#include "../../core/Transform.hpp"

class Renderable : public Transform
{
public:
	using Transform::Transform;

public:
	virtual bool Load() = 0;
	virtual void Display(const Matrix3& a_pojectionMatrix) const = 0;
};

