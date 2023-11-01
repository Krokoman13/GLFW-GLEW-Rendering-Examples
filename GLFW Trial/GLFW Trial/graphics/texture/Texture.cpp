#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

#include <iostream>
#include <string>

bool Texture::NeedsMipmaps(GLint a_param)
{
	return
		a_param == GL_NEAREST_MIPMAP_NEAREST ||
		a_param == GL_LINEAR_MIPMAP_NEAREST ||
		a_param == GL_NEAREST_MIPMAP_LINEAR ||
		a_param == GL_LINEAR_MIPMAP_LINEAR;
}

Texture::Texture(const char* a_filePath) : m_id(), m_filePath(a_filePath)
{
}

bool Texture::Load(GLint a_minFilterParam, GLint a_magFilterParam)
{
	if (m_loaded) return true;

	m_loaded = false;

	if (NeedsMipmaps(a_magFilterParam)) std::cerr << "Warning: Mag filter cannot user mipmaps!";

	glGenTextures(1, &m_id);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glGenTextures failed with error: " << err << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, m_id);

	unsigned char* data = stbi_load(m_filePath, &m_width, &m_height, &m_nrChannels, 0);

	if (data)
	{
		std::cout << "Texure: " << m_filePath << " loaded succesfully" << std::endl;

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, a_minFilterParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, a_magFilterParam);
		// load and generate the texture

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		if (NeedsMipmaps(a_minFilterParam)) glGenerateMipmap(GL_TEXTURE_2D);
		m_loaded = true;
	}
	else
	{
		std::cout << "Failed to load texture: " << m_filePath << " will use a NULL Image instead" << std::endl;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, nullPixelData);

		m_loaded = true;
	}

	stbi_image_free(data);

	return m_loaded;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

const bool Texture::loadCheck() const
{
	if (!m_loaded) {
		std::cout << "Texture: " << m_filePath << " has not been loaded propperly, likely invalid propperty returned" << std::endl;
		return false;
	}

	return true;
}

unsigned int Texture::GetId() const
{
	loadCheck();
	return m_id;
}

int Texture::GetWidth() const
{
	loadCheck();
	return m_width;
}

int Texture::GetHeight() const
{
	loadCheck();
	return m_height;
}

bool Texture::IsLoaded() const
{
	loadCheck();
	return m_loaded;
}