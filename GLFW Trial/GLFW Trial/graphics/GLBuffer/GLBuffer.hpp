#pragma once
#include "../../core/counted/Counted.hpp"
#include "../displayMode/DisplayMode.hpp"

typedef unsigned int GLuint;
typedef float GLfloat;

class GLBuffer : public Counted
{
private:
	GLuint m_bufferID = 0;

public:
	GLBuffer() {};
	GLBuffer(const DisplayMode a_displayMode);
	GLBuffer(const GLfloat* a_floatArray, const unsigned int a_arraySize);
	GLBuffer(const GLBuffer& a_other);
	GLBuffer operator=(const GLBuffer& a_other);
	~GLBuffer() { onDestruction(); }

public:
	inline GLuint GetId() const { return m_bufferID; }
	inline operator GLuint() const{ return GetId(); }

private:
	void onDestruction();
	void initializeBuffer(const GLfloat* a_floatArray, const unsigned int a_arraySize);
};