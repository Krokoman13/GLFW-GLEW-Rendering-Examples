#pragma once
#include "../window/Renderable.hpp"

#include "../Texture/Texture.hpp"
#include "TextureShader.hpp"

#include "../glBuffer/GLBuffer.hpp"

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

	GLBuffer m_vertexBufferId;
	GLBuffer m_uvsBufferId;

	GLint m_minFilterParam = -1;
	GLint m_magFilterParam = -1;

protected:
	virtual void Display(const Matrix3& a_pojectionMatrix) override;
	bool loadTexture();

public:
	inline static GLint defaultMinFilterParam = GL_LINEAR_MIPMAP_LINEAR;
	inline static GLint defaultMagFilterParam = GL_LINEAR;
	inline static DisplayMode defaultDisplayMode = DisplayMode::Center;

	virtual bool Load();
	void SetFilter(GLint a_minFilter, GLint a_magFilter);
};