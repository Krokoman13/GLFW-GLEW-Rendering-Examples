#pragma once
#include "Texture.hpp"
#include "loaders/ShaderUtil.h"

class Image
{
private:
	Texture m_texture;
	GLfloat m_uvs[8];		// 2 triangles, 3 vertices per triangle, 2 floats per vertex = 8 floats in total

public:
	Image(const char* pFilePath);
	virtual ~Image();

	static bool Initialize();
	bool Load();
	void Display();

public:
	float x = 0.f;
	float y = 0.f;

	float xScale = 1.f;
	float yScale = 1.f;

private:
	static bool s_initialized;

	static GLuint s_programID;

	static GLint s_vertexIndex;
	static GLint s_diffuseTextureIndex;
	static GLint s_uvIndex;

	static GLuint s_uvsBufferId;
	static GLuint s_vertexBufferId;
};