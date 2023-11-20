#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

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

Texture::Texture() : m_id()
{

}

Texture::Texture(std::string_view a_filePath) : m_id()
{
	int nrChannels = 0;
	unsigned char* data = stbi_load(a_filePath.data(), &m_width, &m_height, &nrChannels, 4);

	if (data)
	{
		std::cout << "Texure: " << a_filePath << " loaded succesfully" << std::endl;
		initTexture(data, m_width, m_height, defMagFilter, defMinFilter);
		stbi_image_free(data);
		m_succesfullLoadedFromFile = true;
	}
	else
	{
		std::cout << "Failed to load texture: " << a_filePath << " will use a NULL Image instead" << std::endl;
		initTexture(nullPixelData, 2, 2, GL_NEAREST, GL_NEAREST);
	}
}

Texture::Texture(const Texture& a_other) : Counted(a_other), m_id(a_other.m_id)
{
	m_width = a_other.m_width;
	m_height = a_other.m_height;
	m_succesfullLoadedFromFile = a_other.m_succesfullLoadedFromFile;
}


Texture::Texture(const unsigned char* a_data, int a_width, int a_height, GLint a_minFilterParam, GLint a_magFilterParam)
{
	initTexture(a_data, m_width, m_height, a_minFilterParam, a_magFilterParam);
}

void Texture::initTexture(const unsigned char* a_data, int a_width, int a_height, GLint a_minFilterParam, GLint a_magFilterParam)
{
	m_width = a_width;
	m_height = a_height;

	if (NeedsMipmaps(a_magFilterParam)) std::cerr << "Warning: Mag filter cannot user mipmaps!";

	glGenTextures(1, &m_id);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glGenTextures failed with error: " << err << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, m_id);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, a_minFilterParam);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, a_magFilterParam);
	// load and generate the texture

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, a_data);
	if (NeedsMipmaps(a_minFilterParam)) glGenerateMipmap(GL_TEXTURE_2D);
}

bool Texture::NeedsMipmaps(GLint a_param)
{
	return
		a_param == GL_NEAREST_MIPMAP_NEAREST ||
		a_param == GL_LINEAR_MIPMAP_NEAREST ||
		a_param == GL_NEAREST_MIPMAP_LINEAR ||
		a_param == GL_LINEAR_MIPMAP_LINEAR;
}

void Texture::onLastDestruction()
{
	glDeleteTextures(1, &m_id);
}