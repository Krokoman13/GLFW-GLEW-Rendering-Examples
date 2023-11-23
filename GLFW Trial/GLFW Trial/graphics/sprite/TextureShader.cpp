#include <iostream>
#include <stdexcept>

#include "TextureShader.hpp"

TextureShader::TextureShader(const Shader& a_other) : Shader(a_other)
{
	if (a_other.GetProgramID() < 0) throw std::invalid_argument("Cannot convert unloaded texture");
	if (!m_set) setIndexes();
}

void TextureShader::setIndexes()
{
	m_set = true;

	m_uvIndex = GetAttribute("uv");
	if (m_uvIndex == -1) {
		std::cerr << "Error: Could not get uv atribute" << std::endl;
	}

	m_vertexIndex = GetAttribute("vertex");
	if (m_vertexIndex == -1) {
		std::cerr << "Error: Could not get vertex atribute" << std::endl;
	}

	m_diffuseTextureIndex = GetUniform("diffuseTexture");
	if (m_diffuseTextureIndex == -1) {
		std::cerr << "Error: Could not get diffuseTexure uniform" << std::endl;
	}

	m_projectionIndex = GetUniform("projection");
	if (m_diffuseTextureIndex == -1) {
		std::cerr << "Error: Could not get projection uniform" << std::endl;
	}

	m_identityMatrix = GetUniform("identity");
	if (m_identityMatrix == -1) {
		std::cerr << "Error: Could not get identity uniform" << std::endl;
	}
}
