#include "AnimationSprite.hpp"

AnimationSprite::AnimationSprite(const unsigned int a_resourceID, const unsigned int a_columns, const unsigned int a_rows)
	: Sprite(a_resourceID)
{
	m_xValue = 1.f / (float)(m_columns = a_columns);
	m_yValue = 1.f / (float)(m_rows = a_rows);

	m_uvOffset.Set(0, 0, )
}
