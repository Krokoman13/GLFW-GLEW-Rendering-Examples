#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <map>
#include <string>
#include <GL/glew.h>

class Texture
{
protected:
	//OpenGL id for texture buffer
	unsigned int m_id;

	int m_width = 0, m_height = 0;
	int m_nrChannels = 0;

	bool m_loaded = false;

	const char* m_filePath;
	const bool loadCheck() const;

public:
	Texture(const char* pFilePath);
	virtual ~Texture();

	const bool Load();

	unsigned int GetId() const;
	const int GetWidth() const;
	const int GetHeight() const;
	inline const bool IsLoaded() const;
};

#endif // TEXTURE_HPP
