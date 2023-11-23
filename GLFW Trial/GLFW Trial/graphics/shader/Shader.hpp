#pragma once
#include <GL/glew.h>
#include <string_view>
#include "../../core/counted/Counted.hpp"

class Shader : public Counted
{
protected:
	GLuint m_programID = -1;

public:
	Shader() {};
	Shader(GLuint m_programID);
	Shader(const std::string& a_vertex_fragment_Shaderpath);
	Shader(const Shader& a_other) : Counted(a_other), m_programID(a_other.m_programID) {};

protected:
	virtual void onLastDestruction() override { glDeleteProgram(m_programID); }

public:
	inline GLuint GetProgramID() const { return m_programID; }
	inline GLuint GetAttribute(std::string_view a_attribute) const { return glGetAttribLocation(m_programID, a_attribute.data()); }
	inline GLuint GetUniform(std::string_view a_uniform) const { return glGetUniformLocation(m_programID, a_uniform.data()); }
};