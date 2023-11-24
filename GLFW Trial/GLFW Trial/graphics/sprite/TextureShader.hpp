#pragma once
#include "../shader/Shader.hpp"

class TextureShader : public Shader
{
private:
	inline static bool m_set = false;
	inline static GLint m_uvIndex = -1;
	inline static GLint m_vertexIndex = -1;
	inline static GLint m_diffuseTextureIndex = -1;
	inline static GLint m_MVPMatrixIndex = -1;

public:
	TextureShader() {};
	TextureShader(const Shader& a_other);

private:
	void setIndexes();

public:
	inline static GLint GetUvIndex() { return m_uvIndex; }
	inline static GLint GetVertexIndex() { return m_vertexIndex; }
	inline static GLint GetDiffuseTextureIndex() { return m_diffuseTextureIndex; }
	inline static GLint GetMVPMatrix() { return m_MVPMatrixIndex; }
};

