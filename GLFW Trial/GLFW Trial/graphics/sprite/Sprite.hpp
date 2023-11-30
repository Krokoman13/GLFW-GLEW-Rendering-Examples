#pragma once
#include "../window/Renderable.hpp"

#include "../Texture/Texture.hpp"
#include "TextureShader.hpp"

class Sprite : public Renderable
{
public:
	Sprite(const unsigned int a_resourceID);
	virtual ~Sprite();

private:
	const unsigned int m_resourceID;

	Texture m_texture;
	Transform m_textureTransform;

	TextureShader m_texShader;

	GLuint m_vertexBufferId = -1;
	GLuint m_uvsBufferId = -1;

	GLint m_minFilterParam = -1;
	GLint m_magFilterParam = -1;

protected:
	virtual void Display(const Matrix3& a_pojectionMatrix) override;
	bool loadTexture();

public:
	virtual bool Load();
	void SetFilterParam(GLint a_minFilter, GLint a_magFilter);
};