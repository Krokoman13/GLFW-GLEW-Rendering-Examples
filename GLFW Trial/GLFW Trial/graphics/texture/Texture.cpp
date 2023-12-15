#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION 
#include "../loaders/stb_image.h"

#include <iostream>
#include <string>

const unsigned char Texture::nullPixelData[14] = {
	0, 0, 0, // Black pixel
	255, 0, 255,	// Purple pixel

	0, 0, // No idea what these values are for tbh

	255, 0, 255, // Purple pixel
	0, 0, 0  // Black pixel
};

GLint Texture::defMinFilter = GL_LINEAR;
GLint Texture::defMagFilter = GL_LINEAR;

Texture::Texture()
{

}

Texture::Texture(std::string_view a_filePath) : Counted()
{
	int nrChannels = 0;
	unsigned char* data = stbi_load(a_filePath.data(), &m_width, &m_height, &nrChannels, 4);

	if (data)
	{
		std::cout << "Texure: " << a_filePath << " loaded succesfully" << std::endl;
		initTexture(data, m_width, m_height, defMinFilter, defMagFilter);
		stbi_image_free(data);
		m_succesfullLoadedFromFile = true;
	}
	else
	{
		std::cerr << "Failed to load texture: " << a_filePath << " will use a NULL Image instead" << std::endl;
		initTexture(nullPixelData, 2, 2, GL_NEAREST, GL_NEAREST);
	}
}

Texture::Texture(const Texture& a_other) : Counted(a_other), m_id(a_other.m_id)
{
	m_width = a_other.m_width;
	m_height = a_other.m_height;
	m_succesfullLoadedFromFile = a_other.m_succesfullLoadedFromFile;
}

Texture Texture::operator=(const Texture& a_other)
{
	onDestruction();

	Counted::operator=(a_other);

	m_id = a_other.m_id;
	m_width = a_other.m_width;
	m_height = a_other.m_height;
	m_succesfullLoadedFromFile = a_other.m_succesfullLoadedFromFile;

	return *this;
}

Texture::Texture(const unsigned char* a_data, int a_width, int a_height, GLint a_minFilterParam, GLint a_magFilterParam)
{
	initTexture(a_data, m_width, m_height, a_minFilterParam, a_magFilterParam);
}

void Texture::initTexture(const unsigned char* a_data, int a_width, int a_height, GLint a_minFilterParam, GLint a_magFilterParam)
{
	m_width = a_width;
	m_height = a_height;

	if (NeedsMipmaps(a_magFilterParam)) 
		std::cerr << "Warning: Mag filter cannot user mipmaps!" << std::endl;

	glGenTextures(1, &m_id);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glGenTextures failed with error: " << err << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, m_id);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glBindTexture failed with error: " << err << std::endl;
	}

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glTexParameteri1 failed with error: " << err << std::endl;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glTexParameteri2 failed with error: " << err << std::endl;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, a_minFilterParam);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glTexParameteri3 failed with error: " << err << std::endl;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, a_magFilterParam);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glTexParameteri4 failed with error: " << err << std::endl;
	}
	// load and generate the texture

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, a_data);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glTexImage2D failed with error: " << err << std::endl;
	}

	if (!NeedsMipmaps(a_minFilterParam)) return;

	glGenerateMipmap(GL_TEXTURE_2D);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glGenerateMipmap failed with error: " << err << std::endl;
	}
}

bool Texture::NeedsMipmaps(GLint a_param)
{
	return
		a_param == GL_NEAREST_MIPMAP_NEAREST ||
		a_param == GL_LINEAR_MIPMAP_NEAREST ||
		a_param == GL_NEAREST_MIPMAP_LINEAR ||
		a_param == GL_LINEAR_MIPMAP_LINEAR;
}

void Texture::onDestruction()
{
	if (m_id == 0 || !IsLast()) return;

	glDeleteTextures(1, &m_id);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glDeleteTextures failed with error: " << err << std::endl;
	}
}