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
	m_vertexIndex = GetAttribute("vertex");
	if (m_vertexIndex == -1) {
		std::cerr << "Error: Could not get vertex atribute" << std::endl;
	}

	m_uvIndex = GetAttribute("uv");
	if (m_uvIndex == -1) {
		std::cerr << "Error: Could not get uv atribute" << std::endl;
	}

	m_MVPMatrixIndex = GetUniform("mvp");
	if (m_MVPMatrixIndex == -1) {
		std::cerr << "Error: Could not get mvp uniform" << std::endl;
	}

	m_diffuseTextureIndex = GetUniform("diffuseTexture");
	if (m_diffuseTextureIndex == -1) {
		std::cerr << "Error: Could not get diffuseTexure uniform" << std::endl;
	}
}
