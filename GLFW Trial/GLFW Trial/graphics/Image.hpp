#pragma once
#include "Texture.hpp"
#include "window/Renderable.hpp"

class Image : public Renderable
{
public:
	Image(const char* pFilePath);
	virtual ~Image();

public:
	GLint minFilterParam = -1;
	GLint magFilterParam = -1;

	float x = 0.f;
	float y = 0.f;

	float xScale = 1.f;
	float yScale = 1.f;

private:
	Texture m_texture;

	GLuint m_programID = -1;

	GLint m_vertexIndex = -1;
	GLint m_diffuseTextureIndex = -1;
	GLint m_uvIndex = -1;
	GLint m_offsetIndex = -1;
	GLint m_scaleIndex = -1;

	GLuint m_uvsBufferId = -1;
	GLuint m_vertexBufferId = -1;

public:
	virtual bool Load();
	virtual void Display();

private:
	bool useDefaultImageVariables();
};