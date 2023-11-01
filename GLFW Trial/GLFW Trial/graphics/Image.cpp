#include "Image.hpp"
#include <iostream>
#include "DefaultImageVariables.hpp"

Image::Image(const char* pFilePath)
{
	m_texture = TextureMapper::Get(pFilePath);
}

Image::~Image()
{
	//Destroy shader program
	//glDeleteProgram(s_programID);
}

bool Image::Load()
{
	bool succesful = true;

	if (m_minFilterParam < 0) m_minFilterParam = DefaultImageVariables::minFilterParam;
	if (m_magFilterParam < 0) m_magFilterParam = DefaultImageVariables::magFilterParam;

	if (!m_texture.Get().Load(m_minFilterParam, m_magFilterParam)) {
		std::cerr << "Error: Could not load texture" << std::endl;
		succesful = false;
	}

	if (!useDefaultImageVariables()) {
		std::cerr << "Error: Could not use defaultImageVariables" << std::endl;
		succesful = false;
	}

	return succesful;
}

bool Image::useDefaultImageVariables()
{
	bool succesful = DefaultImageVariables::Initialize();

	m_programID = DefaultImageVariables::GetProgramID();

	m_vertexIndex = DefaultImageVariables::GetVertexIndex();
	m_diffuseTextureIndex = DefaultImageVariables::GetDiffuseTextureIndex();
	m_uvIndex = DefaultImageVariables::GetUvIndex();
	m_scaleIndex = DefaultImageVariables::GetScaleIndex();
	m_offsetIndex = DefaultImageVariables::GetOffsetIndex();

	m_uvsBufferId = DefaultImageVariables::GetUvsBufferId();
	m_vertexBufferId = DefaultImageVariables::GetVertexBufferId();

	return succesful;
}

void Image::SetFilterParam(GLint a_minFilter, GLint a_magFilter)
{
	if (Texture::NeedsMipmaps(a_magFilter))
	{
		std::cerr << "Warning: Mag filter cannot user mipmaps!";
		return;
	}

	m_minFilterParam = a_minFilter;
	m_magFilterParam = a_magFilter;
}

void Image::Display()
{
	//tell the GPU to use this program
	glUseProgram(m_programID);

	glUniform2f(m_scaleIndex, xScale, yScale);
	glUniform2f(m_offsetIndex, x, y);
	//glUniform2f(glGetUniformLocation(s_programID, "rotation"), rotation);

	//tell OpenGL that the data for the vertexIndex is coming in from an array
	glEnableVertexAttribArray(m_vertexIndex);
	//bind the buffer with data.
	//the moment this buffer is bound instead of 0, the last param of glVertexAttribPointer
	//is interpreted as an offset and not a pointer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	//send the data for this index to OpenGL, specifying it's format and structure
	//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
	glVertexAttribPointer(m_vertexIndex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//tell OpenGL that the data for the vertexIndex/colorIndex is coming in from an array
	glEnableVertexAttribArray(m_uvIndex);
	//bind the buffer with data.
	//the moment this buffer is bound instead of 0, the last param of glVertexAttribPointer
	//is interpreted as an offset and not a pointer
	glBindBuffer(GL_ARRAY_BUFFER, m_uvsBufferId);
	//send the data for this index to OpenGL, specifying it's format and structure
	//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
	glVertexAttribPointer(m_uvIndex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, m_texture.Get().GetId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(m_diffuseTextureIndex, 0);

	//Draws elements from each enabled array using the specified mode (which is default for Unity etc as well)
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(m_vertexIndex);
	glDisableVertexAttribArray(m_uvIndex);
}
