#include "AnimationSprite.hpp"
#include <glew.h>

#include "../../../resourceManager/ResourceManager.hpp"
#include "../../../Resources/fileIndex.hpp"

AnimationSprite::AnimationSprite(const unsigned int a_resourceID, const unsigned int a_columns, const unsigned int a_rows)
	: Sprite(a_resourceID)
{
	m_xValue = 1.f / (float)(m_columns = a_columns);
	m_yValue = 1.f / (float)(m_rows = a_rows);

	m_uvOffset.Scale(Vec2(m_xValue, m_yValue));
}

void AnimationSprite::SetCurrentFrame(const unsigned int a_frame)
{
	if (a_frame >= (m_columns * m_rows)) throw std::out_of_range("Frame does not exist");

	m_uvOffset.SetXPos(m_xValue * (a_frame % m_columns));
	m_uvOffset.SetYPos(m_yValue * (a_frame / m_columns));
}

void AnimationSprite::Display(const Matrix3& a_pojectionMatrix) const
{
	//tell the GPU to use this program
	glUseProgram(m_texShader.GetProgramID());

	Matrix modelView = a_pojectionMatrix * m_textureTransform.GetGlobalMatrix();
	glUniformMatrix3fv(m_texShader.GetMVPMatrix(), 1, GL_FALSE, modelView.GetArray().Data());

	glUniform4f(m_texShader.GetDiffuseColorIndex(),
		diffuseColor.GetRedUnit(),
		diffuseColor.GetGreenUnit(),
		diffuseColor.GetBlueUnit(),
		diffuseColor.GetAlphaUnit()
	);

	GLuint uvOffsetIndex = m_texShader.GetUniform("uvOffset");
	glUniformMatrix3fv(uvOffsetIndex, 1, GL_FALSE, m_uvOffset.GetArray().Data());

	//tell OpenGL that the data for the vertexIndex is coming in from an array
	glEnableVertexAttribArray(m_texShader.GetVertexIndex());
	//bind the buffer with data.
	//the moment this buffer is bound instead of 0, the last param of glVertexAttribPointer
	//is interpreted as an offset and not a pointer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//send the data for this index to OpenGL, specifying it's format and structure
	//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
	glVertexAttribPointer(m_texShader.GetVertexIndex(), 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//tell OpenGL that the data for the vertexIndex/colorIndex is coming in from an array
	glEnableVertexAttribArray(m_texShader.GetUvIndex());
	//bind the buffer with data.
	//the moment this buffer is bound instead of 0, the last param of glVertexAttribPointer
	//is interpreted as an offset and not a pointer
	glBindBuffer(GL_ARRAY_BUFFER, m_uvsBuffer);
	//send the data for this index to OpenGL, specifying it's format and structure
	//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
	glVertexAttribPointer(m_texShader.GetUvIndex(), 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, m_texture.GetId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(m_texShader.GetDiffuseTextureIndex(), 0);

	//Draws elements from each enabled array using the specified mode (which is default for Unity etc as well)
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(m_texShader.GetVertexIndex());
	glDisableVertexAttribArray(m_texShader.GetUvIndex());
}

bool AnimationSprite::loadShader()
{
	m_texShader = ResourceManager::GetShader(RS__TEXTUREUVOFFSET_VERT, RS__TEXTURE_FRAG);

	return m_texShader.GetProgramID() != 0;
}
