#pragma once
#include "Texture/Texture.hpp"
#include "window/Renderable.hpp"

#include "../ResourceCache.hpp"

class Sprite : public Renderable
{
public:
	Sprite(const char* pFilePath);
	virtual ~Sprite();

public:
	static ResourceCache<Texture>* pTextureCache;

private:
	const char* m_filepath;

	Texture m_texture;
	Transform m_textureTransform;

	GLuint m_programID = -1;

	GLint m_vertexIndex = -1;
	GLint m_diffuseTextureIndex = -1;
	GLint m_uvIndex = -1;
	GLint m_projectionIndex = -1;
	GLint m_identityMatrix = -1;

	GLuint m_uvsBufferId = -1;
	GLuint m_vertexBufferId = -1;

	GLint m_minFilterParam = -1;
	GLint m_magFilterParam = -1;

protected:
	virtual void Display(const Matrix3& a_pojectionMatrix) override;

public:
	virtual bool Load();

	void SetFilterParam(GLint a_minFilter, GLint a_magFilter);

private:
	bool useDefaultImageVariables();
};