#pragma once
#include "../shader/Shader.hpp"

class TextureShader : public Shader
{
private:
	inline static bool m_set = false;
	inline static GLint m_uvIndex = -1;
	inline static GLint m_vertexIndex = -1;
	inline static GLint m_diffuseTextureIndex = -1;
	inline static GLint m_projectionIndex = -1;
	inline static GLint m_identityMatrix = -1;

public:
	TextureShader() {};
	TextureShader(const Shader& a_other);

private:
	void setIndexes();

public:
	inline static GLint GetUvIndex() { return m_uvIndex; }
	inline static GLint GetVertexIndex() { return m_vertexIndex; }
	inline static GLint GetDiffuseTextureIndex() { return m_diffuseTextureIndex; }
	inline static GLint GetProjectionIndex() { return m_projectionIndex; }
	inline static GLint GetIdenityMatrix() { return m_identityMatrix; }
};

