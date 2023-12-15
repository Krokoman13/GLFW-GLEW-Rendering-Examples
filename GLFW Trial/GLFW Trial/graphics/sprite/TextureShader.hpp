#pragma once
#include "../shader/Shader.hpp"

class TextureShader : public Shader
{
private:
	GLint m_uvIndex = -1;
	GLint m_vertexIndex = -1;
	GLint m_diffuseTextureIndex = -1;
	GLint m_diffuseColorIndex = -1;
	GLint m_MVPMatrixIndex = -1;

public:
	TextureShader() {};
	TextureShader(const Shader& a_other);
	TextureShader operator=(const Shader& a_other);

public:
	inline GLint GetUvIndex() const { return m_uvIndex; }
	inline GLint GetVertexIndex() const { return m_vertexIndex; }
	inline GLint GetDiffuseTextureIndex() const { return m_diffuseTextureIndex; }
		inline GLint GetDiffuseColorIndex() const { return m_diffuseColorIndex; }
	inline GLint GetMVPMatrix() const { return m_MVPMatrixIndex; }

private:
	void setIndexes();
};

