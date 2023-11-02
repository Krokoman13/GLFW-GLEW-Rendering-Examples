#include <string>
#include <GL/glew.h>


class Texture
{
private:
	const unsigned char nullPixelData[14] = {
		0, 0, 0, // Black pixel
		255, 0, 255,	// Purple pixel

		0, 0, // No idea what these values are for tbh

		255, 0, 255, // Purple pixel
		0, 0, 0  // Black pixel
	};

protected:
	//OpenGL id for texture buffer
	unsigned int m_id;

	int m_width = 0, m_height = 0;
	int m_nrChannels = 0;

	bool m_loaded = false;

	const char* m_filePath;
	const bool loadCheck() const;

public:
	Texture(const char* a_filePath);
	virtual ~Texture();

	static bool NeedsMipmaps(GLint a_param);

	bool Load(GLint a_minFilterParam = GL_LINEAR, GLint a_magFilterParam = GL_LINEAR);

	unsigned int GetId() const;
	int GetWidth() const;
	int GetHeight() const;

	inline const char* GetFilePath() const { return m_filePath; };
	inline bool IsLoaded() const;
};