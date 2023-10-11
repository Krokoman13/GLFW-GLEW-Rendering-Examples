#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

#include <iostream>
#include <string>

Texture::Texture(const char* pFilePath): m_id(), m_filePath(pFilePath)
{

}

const bool Texture::Load()
{
    m_loaded = false;

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	unsigned char* data = stbi_load(m_filePath, &m_width, &m_height, &m_nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		m_loaded = true;
	}
	else
	{
		std::cout << "Failed to load texture: " << m_filePath << std::endl;
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

const int Texture::GetWidth() const
{
    loadCheck();
    return m_width;
}

const int Texture::GetHeight() const
{
    loadCheck();
    return m_height;
}

const bool Texture::IsLoaded() const
{
    loadCheck();
    return m_loaded;
}










