#include "HologramSprite.hpp"
#include "../../resourceManager/ResourceManager.hpp"
#include "../../Resources/fileIndex.hpp"

HologramSprite::HologramSprite(const unsigned int a_resourceID) : Sprite(a_resourceID), m_time(0)
{
	diffuseColor = Color(173, 216, 230, 200);
}

void HologramSprite::Display(const Matrix3& a_pojectionMatrix) const
{
	Sprite::initializeShader();

	GLuint time = m_texShader.GetUniform("time");
	m_time += speed;
	glUniform1f(time, m_time);

	Sprite::setShaderValues(a_pojectionMatrix);

	Sprite::drawAndDisableArrays();
}

bool HologramSprite::loadShader()
{
	m_texShader = ResourceManager::GetShader(RS__HOLOGRAM_VERT, RS__HOLOGRAM_FRAG);

	return m_texShader.GetProgramID() != 0;
}
