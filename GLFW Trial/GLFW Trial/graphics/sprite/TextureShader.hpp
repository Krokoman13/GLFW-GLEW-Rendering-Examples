#pragma once
#include "../shader/Shader.hpp"

class TextureShader : public Shader
{
private:
	GLint m_vertexIndex = -1;
	GLint m_uvIndex = -1;
	GLint m_MVPMatrixIndex = -1;
	GLint m_uvOffsetIndex = -1;
	GLint m_diffuseTextureIndex = -1;
	GLint m_diffuseColorIndex = -1;


public:
	TextureShader() {};
	TextureShader(const Shader& a_other);
	TextureShader operator=(const Shader& a_other);

public:
	inline GLint GetVertexIndex() const { return m_vertexIndex; }
	inline GLint GetUvIndex() const { return m_uvIndex; }
	inline GLint GetDiffuseColorIndex() const { return m_diffuseColorIndex; }
	inline GLint GetUVOffsetIndex() const { return m_uvOffsetIndex; }
	inline GLint GetDiffuseTextureIndex() const { return m_diffuseTextureIndex; }
	inline GLint GetMVPMatrix() const { return m_MVPMatrixIndex; }

private:
	void setIndexes();
};

