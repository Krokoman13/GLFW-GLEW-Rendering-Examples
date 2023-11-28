#pragma once
#include "../../core/counted/Counted.hpp"

typedef unsigned int GLuint;
typedef float GLfloat;

class GLBuffer : public Counted
{
private:
	GLuint m_id = 0;
	unsigned int m_arraySize = 0;

public:
	GLBuffer() {};
	GLBuffer(const GLfloat* a_floatArray, const unsigned int a_arraySize);
	GLBuffer(const GLBuffer& a_other);
	GLBuffer operator=(const GLBuffer& a_other);

protected:
	virtual void onLastDestruction() override;

public:
	inline operator GLuint() { return m_id; }
};