#include "DefaultImageVariables.hpp"
#include <iostream>
#include "loaders/ShaderUtil.hpp"

bool DefaultSpriteVariables::m_initialized = false;

GLuint DefaultSpriteVariables::m_programID = -1;

GLint DefaultSpriteVariables::m_vertexIndex = -1;
GLint DefaultSpriteVariables::m_diffuseTextureIndex = -1;
GLint DefaultSpriteVariables::m_uvIndex = -1;
GLint DefaultSpriteVariables::m_offsetIndex = -1;
GLint DefaultSpriteVariables::m_axisIndex = -1;

GLuint DefaultSpriteVariables::m_uvsBufferId = -1;
GLuint DefaultSpriteVariables::m_vertexBufferId = -1;

GLint DefaultSpriteVariables::minFilterParam = GL_LINEAR;
GLint DefaultSpriteVariables::magFilterParam = GL_LINEAR;

/*
if (!m_initialized)
{
	std::cout << "Static variables of Image class not Initialized" << std::endl;
	std::cout << "Initializing static variables of image class..." << std::endl;

	if (Initialize()) std::cout << "Initialization complete!" << std::endl;
	else std::cerr << "Initialization failed!" << std::endl;
}
*/

bool DefaultSpriteVariables::Initialize()
{
	if (m_initialized)
	{
		std::cout << "DefaultImageVariables is already initialized, no longer needed!" << std::endl;
		return true;
	}

	bool succesful = true;

	// Create the shader program
	m_programID = ShaderUtil::createProgram("texture.vert", "texture.frag");
	if (m_programID == -1) {
		std::cerr << "Error: Could not create program" << std::endl;
		succesful = false;
	}

	// get index for the attributes in the shader
	m_vertexIndex = glGetAttribLocation(m_programID, "vertex");
	if (m_vertexIndex == -1) {
		std::cerr << "Error: Could not get vertex atribute" << std::endl;
		succesful = false;
	}

	m_uvIndex = glGetAttribLocation(m_programID, "uv");
	if (m_uvIndex == -1) {
		std::cerr << "Error: Could not get uv atribute" << std::endl;
		succesful = false;
	}

	m_diffuseTextureIndex = glGetUniformLocation(m_programID, "diffuseTexture");
	if (m_diffuseTextureIndex == -1) {
		std::cerr << "Error: Could not get diffuseTexure atribute" << std::endl;
		succesful = false;
	}

	m_offsetIndex = glGetUniformLocation(m_programID, "offset");
	if (m_axisIndex == -1) {
		std::cerr << "Error: Could not get offset atribute" << std::endl;
		succesful = false;
	}

	m_axisIndex = glGetUniformLocation(m_programID, "axis");
	if (m_axisIndex == -1) {
		std::cerr << "Error: Could not get axis atribute" << std::endl;
		succesful = false;
	}

	const GLfloat vertices[8] = {
		//2 triangles forming a rectangle, 3 vertices per triangle, 2 floats per vertex = 8 floats in total
		-0.5f,  0.5f,  // Top left
		-0.5f, -0.5f,  // Bottom left
		 0.5f,  0.5f,  // Top right
		 0.5f, -0.5f,  // Bottom right
	};

	//create a handle to the buffer
	glGenBuffers(1, &m_vertexBufferId);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glGenBuffers failed with error: " << err << std::endl;
	}

	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	//stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	//note that vertexPositionsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	const GLfloat uvs[8] = {
		//2 triangles forming a rectangle, 3 vertices per triangle, 2 floats per vertex = 8 floats in total
		0.f, 1.f,  // Top left
		0.f, 0.f,  // Bottom left
		1.f, 1.f,  // Top right
		1.f, 0.f,  // Bottom right
	};

	// create a handle to the buffer
	glGenBuffers(1, &m_uvsBufferId);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glGenBuffers failed with error: " << err << std::endl;
	}
	// bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	// a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, m_uvsBufferId);
	// stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
	// disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return m_initialized = succesful;
}

//Destroy shader program
//glDeleteProgram(s_programID);
