#include "GLBuffer.hpp"
#include <iostream>
#include <gl/glew.h>

GLBuffer::GLBuffer(const GLfloat* a_floatArray, const unsigned int a_arraySize) : m_arraySize(a_arraySize)
{
	// create a handle to the buffer
	glGenBuffers(1, &m_id);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glGenBuffers failed with error: " << err << std::endl;
	}

	// bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	// a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, m_id);

	// stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	glBufferData(GL_ARRAY_BUFFER, m_arraySize * sizeof(GLfloat), a_floatArray, GL_STATIC_DRAW);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glBufferData failed with error: " << err << std::endl;
	}

	// disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLBuffer::GLBuffer(const GLBuffer& a_other)
{
	m_id = a_other.m_id;
	m_arraySize = a_other.m_arraySize;
}

GLBuffer GLBuffer::operator=(const GLBuffer& a_other)
{
	onDestruction();

	Counted::operator=(a_other);

	m_id = a_other.m_id;
	m_arraySize = a_other.m_arraySize;
	return *this;
}

void GLBuffer::onDestruction()
{
	if (m_id == 0 || !IsLastCopy()) return; // If m_bufferID was not bound to anything don't delete buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_id);
}
