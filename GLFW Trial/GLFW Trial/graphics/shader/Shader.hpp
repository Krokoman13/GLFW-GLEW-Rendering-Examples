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
	Shader operator=(const Shader& a_other);
	~Shader() { onDestsruction(); }

public:
	inline GLuint GetProgramID() const { return m_programID; }
	GLuint GetAttribute(std::string_view a_attribute) const;
	GLuint GetUniform(std::string_view a_uniform) const;

private:
	void onDestsruction();
};