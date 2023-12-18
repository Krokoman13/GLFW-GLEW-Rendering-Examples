#pragma once
#include "../../graphics/sprite/Sprite.hpp"

class HologramSprite : public Sprite
{
private:
	mutable float m_time;

public:
	float speed = 0.01f;

public:
	HologramSprite(const unsigned int a_resourceID);
	virtual void Display(const Matrix3& a_pojectionMatrix) const override;

protected:
	virtual bool loadShader() override;
};

