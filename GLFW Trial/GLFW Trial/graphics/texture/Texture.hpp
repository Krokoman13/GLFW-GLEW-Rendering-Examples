#include <string>
#include <GL/glew.h>
#include <string_view>

#include "../../Counted.hpp"

class Texture : public Counted
{
private:
	const static unsigned char nullPixelData[14];
	Texture(const unsigned char* a_data, int a_width, int a_height, GLint a_minFilterParam, GLint a_magFilterParam);
	void initTexture(const unsigned char* a_data, int a_width, int a_height, GLint a_minFilterParam, GLint a_magFilterParam);

protected:
	//OpenGL id for texture buffer
	unsigned int m_id;

	bool m_succesfullLoadedFromFile = false;
	int m_width = 0, m_height = 0;

	void onLastDestruction() override;

public:
	Texture();
	Texture(std::string_view a_filePath, GLint a_minFilterParam, GLint a_magFilterParam);
	Texture(const Texture& a_other);

	static bool NeedsMipmaps(GLint a_param);

	inline bool SuccesfullLoad() const { return m_succesfullLoadedFromFile; };
	inline int GetId() const { return m_id; };
	inline int GetWidth() const { return m_width; };
	inline int GetHeight() const { return m_height; };
};
