#include <iostream>
#include "Shader.hpp"
#include "../loaders/ShaderUtil.hpp"

Shader::Shader(GLuint a_programID)
{
	m_programID = a_programID;

	if (m_programID == -1) {
		std::cerr << "Error: Could not create shader program" << std::endl;
	}
}

Shader::Shader(const std::string& a_vertex_fragment_Shaderpath)
{
	m_programID = ShaderUtil::createProgram(a_vertex_fragment_Shaderpath);

	if (m_programID == -1) {
		std::cerr << "Error: Could not create shader program" << std::endl;
	}
}
