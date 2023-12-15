#pragma once
#include "../Sprite.hpp"

class AnimationSprite : public Sprite
{
private:
	Matrix3 m_uvOffset;
	unsigned int m_columns;
	unsigned int m_rows;

	float m_xValue;
	float m_yValue;

public:
	AnimationSprite(const unsigned int a_resourceID, const unsigned int a_columns, const unsigned int a_rows);

public:
	void SetCurrentFrame(const unsigned int a_frame);
	virtual void Display(const Matrix3& a_pojectionMatrix) const override;

protected:
	virtual bool loadShader() override;
};

