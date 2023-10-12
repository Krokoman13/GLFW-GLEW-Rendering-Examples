#pragma once
#include <GL/glew.h>

class DefaultImageVariables
{
private:
	static bool m_initialized;

	static GLuint m_programID;

	static GLint m_vertexIndex;
	static GLint m_uvIndex;
	static GLint m_diffuseTextureIndex;
	static GLint m_offsetIndex;
	static GLint m_scaleIndex;

	static GLuint m_vertexBufferId;
	static GLuint m_uvsBufferId;

public:
	static bool Initialize();

	static GLint minFilterParam;
	static GLint magFilterParam;

	inline static const GLuint GetProgramID() { return m_programID; }

	inline static const GLint GetVertexIndex() { return m_vertexIndex; }
	inline static const GLint GetDiffuseTextureIndex() { return m_diffuseTextureIndex; }
	inline static const GLint GetUvIndex() { return m_uvIndex; }
	inline static const GLint GetScaleIndex() { return m_scaleIndex; }
	inline static const GLint GetOffsetIndex() { return m_offsetIndex; }

	inline static const GLuint GetUvsBufferId() { return m_uvsBufferId; }
	inline static const GLuint GetVertexBufferId() { return m_vertexBufferId; }
};

