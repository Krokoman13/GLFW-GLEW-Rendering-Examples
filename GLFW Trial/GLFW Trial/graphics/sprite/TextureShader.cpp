#include <iostream>
#include <stdexcept>

#include "TextureShader.hpp"

TextureShader::TextureShader(const Shader& a_other) : Shader(a_other)
{
	if (a_other.GetProgramID() < 0) throw std::invalid_argument("Cannot convert unloaded texture");

	setIndexes();
}

TextureShader TextureShader::operator=(const Shader& a_other)
{
	Shader::operator=(a_other);

	setIndexes();

	return *this;
}

void TextureShader::setIndexes()
{	
	m_uvIndex = GetAttribute("uv");
	m_vertexIndex = GetAttribute("vertex");
	m_MVPMatrixIndex = GetUniform("mvp");
	m_uvOffsetIndex = GetUniform("uvOffset");
	m_diffuseTextureIndex = GetUniform("diffuseTexture");
	m_diffuseColorIndex = GetUniform("diffuseColor");
}
