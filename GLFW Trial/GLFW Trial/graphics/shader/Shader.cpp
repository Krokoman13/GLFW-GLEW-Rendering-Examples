#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.hpp"
#include "../loaders/ShaderUtil.hpp"

Shader::Shader(GLuint a_programID)
{
	m_programID = a_programID;

	if (m_programID <= 0) {
		throw std::invalid_argument("Invalid ShaderProgram");
	}
}

Shader::Shader(const std::string& a_vertex_fragment_Shaderpath) : Shader(ShaderUtil::createProgram(a_vertex_fragment_Shaderpath))
{

}

Shader Shader::operator=(const Shader& a_other)
{
	onDestsruction();

	Counted::operator=(a_other);

	m_programID = a_other.m_programID;

	return *this;
}

void Shader::onDestsruction()
{
	if (m_programID == -1 || !IsLastCopy()) return;

	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "unknown error: " << err << std::endl;
	}

	glDeleteProgram(m_programID);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glDeleteProgram failed with error: " << err << std::endl;
	}
}

GLuint Shader::GetAttribute(std::string_view a_attribute) const
{
	GLuint attributeLocation = glGetAttribLocation(m_programID, a_attribute.data());
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glGetAttribLocation `" << a_attribute << "` failed with error: " << err << std::endl;
	}
	return attributeLocation;
}

GLuint Shader::GetUniform(std::string_view a_uniform) const
{
	GLuint uniformLocation = glGetUniformLocation(m_programID, a_uniform.data());
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glGetUniformLocation `" << a_uniform << "` failed with error: " << err << std::endl;
	}
	return uniformLocation;
}
