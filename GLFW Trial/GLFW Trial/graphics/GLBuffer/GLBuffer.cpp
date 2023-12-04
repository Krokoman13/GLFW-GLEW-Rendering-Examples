#include "GLBuffer.hpp"
#include <iostream>
#include <gl/glew.h>

GLBuffer::GLBuffer(const DisplayMode a_displayMode)
{
	GLfloat* floatArray;
	const int size = 8;

	switch (a_displayMode) {
	case TopLeft:
		floatArray = new GLfloat[size]{
			 0.f,  1.f,  // Top left
			 0.f,  0.f,  // Bottom left
			 1.f,  1.f,  // Top right
			 1.f,  0.f,  // Bottom right
		};
		break;
	case TopRight: 
		floatArray = new GLfloat[size]{
			-1.f,  1.f,  // Top left
			-1.f,  0.f,  // Bottom left
			 0.f,  1.f,  // Top right
			 0.f,  0.f,  // Bottom right
		};
		break;
	case Center:
		floatArray = new GLfloat[size]{
			-0.5f,  0.5f,  // Top left
			-0.5f, -0.5f,  // Bottom left
			 0.5f,  0.5f,  // Top right
			 0.5f, -0.5f,  // Bottom right
		};
		break;
	case BottomLeft:
		floatArray = new GLfloat[size]{
			-1.f,  1.f,  // Top left
			-1.f,  0.f,  // Bottom left
			 0.f,  1.f,  // Top right
			 0.f,  0.f,  // Bottom right
		};
		break;
	case BottomRight:
		floatArray = new GLfloat[size]{
			-1.f,  0.f,  // Top left
			-1.f, -1.f,  // Bottom left
			 0.f,  0.f,  // Top right
			 0.f, -1.f,  // Bottom right
		};
		break;
	default:
		throw std::invalid_argument("One or more displaymodes are not implimented");
		break;
	}

	initializeBuffer(floatArray, size);
	delete[] floatArray;
}

GLBuffer::GLBuffer(const GLfloat* a_floatArray, const unsigned int a_arraySize)
{
	initializeBuffer(a_floatArray, a_arraySize);
}

GLBuffer::GLBuffer(const GLBuffer& a_other) : Counted(a_other)
{
	m_bufferID = a_other.m_bufferID;
}

GLBuffer GLBuffer::operator=(const GLBuffer& a_other)
{
	onDestruction();

	Counted::operator=(a_other);

	m_bufferID = a_other.m_bufferID;
	return *this;
}

void GLBuffer::onDestruction()
{
	if (m_bufferID == 0 || !IsLast()) return; // If m_bufferID was not bound to anything don't delete buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_bufferID);
}

void GLBuffer::initializeBuffer(const GLfloat* a_floatArray, const unsigned int a_arraySize)
{
	// create a handle to the buffer
	glGenBuffers(1, &m_bufferID);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glGenBuffers failed with error: " << err << std::endl;
	}

	// bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	// a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);

	// stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	glBufferData(GL_ARRAY_BUFFER, a_arraySize * sizeof(GLfloat), a_floatArray, GL_STATIC_DRAW);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glBufferData failed with error: " << err << std::endl;
	}

	// disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
