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

	bool needsMipmaps(GLint a_param);

public:
	Texture(const char* a_filePath);
	virtual ~Texture();

	const bool Load(GLint a_minFilterParam = GL_LINEAR, GLint a_magFilterParam = GL_LINEAR);

	const unsigned int GetId() const;
	const int GetWidth() const;
	const int GetHeight() const;
	inline const bool IsLoaded() const;
};
