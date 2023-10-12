#include "Image.hpp"

bool Image::s_initialized = false;

GLuint Image::s_programID = -1;

GLint Image::s_vertexIndex = -1;
GLint Image::s_diffuseTextureIndex = -1;
GLint Image::s_uvIndex = -1;

GLuint Image::s_uvsBufferId = -1;
GLuint Image::s_vertexBufferId = -1;

Image::Image(const char* pFilePath)
	: m_texture(pFilePath),
	m_uvs{
	0.0f, 0.0f,  // Bottom left corner
	1.0f, 0.0f,  // Bottom right corner
	0.0f, 1.0f,  // Top left corner
	1.0f, 1.0f   // Top right corner
	}
{

}

Image::~Image()
{
	//Destroy shader program
	//glDeleteProgram(s_programID);
}

bool Image::Initialize()
{
	bool succesful = true;

	// Create the shader program
	s_programID = ShaderUtil::createProgram("texture.vert", "texture.frag");
	if (s_programID == -1) {
		std::cerr << "Error: Could not create program" << std::endl;
		succesful = false;
	}

	// get index for the attributes in the shader
	s_vertexIndex = glGetAttribLocation(s_programID, "vertex");
	if (s_vertexIndex == -1) {
		std::cerr << "Error: Could not get vertex atribute" << std::endl;
		succesful = false;
	}

	s_uvIndex = glGetAttribLocation(s_programID, "uv");
	if (s_uvIndex == -1) {
		std::cerr << "Error: Could not get uv atribute" << std::endl;
		succesful = false;
	}

	s_diffuseTextureIndex = glGetUniformLocation(s_programID, "diffuseTexture");
	if (s_diffuseTextureIndex == -1) {
		std::cerr << "Error: Could not get diffuseTexure atribute" << std::endl;
		succesful = false;
	}

	const GLfloat vertices[8] = {
		//2 triangles forming a rectangle, 3 vertices per triangle, 2 floats per vertex = 8 floats in total
		0.f, 1.f,  // Top left
		0.f, 0.f,  // Bottom left
		1.f, 1.f,  // Top right
		1.f, 0.f,  // Bottom right
	};

	//create a handle to the buffer
	glGenBuffers(1, &s_vertexBufferId);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glGenBuffers failed with error: " << err << std::endl;
	}

	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, s_vertexBufferId);
	//stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	//note that vertexPositionsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return s_initialized = succesful;
}

bool Image::Load()
{
	bool succesful = true;
	
	if (!s_initialized)
	{
		std::cout << "Static variables of Image class not Initialized" << std::endl;
		std::cout << "Initializing static variables of image class..." << std::endl;
		
		if (Initialize()) std::cout << "Initialization complete!" << std::endl;
		else std::cerr << "Initialization failed!" << std::endl;
	}

	if (!m_texture.Load()) {
		std::cerr << "Error: Could not load texture" << std::endl;
		succesful = false;
	}

	// create a handle to the buffer
	glGenBuffers(1, &s_uvsBufferId);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glGenBuffers failed with error: " << err << std::endl;
	}
	// bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	// a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, s_uvsBufferId);
	// stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_uvs), m_uvs, GL_STATIC_DRAW);
	// disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return succesful;
}

void Image::Display()
{
	//tell the GPU to use this program
	glUseProgram(s_programID);

	glUniform2f(glGetUniformLocation(s_programID, "scale"), xScale, yScale);
	glUniform2f(glGetUniformLocation(s_programID, "offset"), x, y);
	//glUniform2f(glGetUniformLocation(s_programID, "rotation"), rotation);

	//tell OpenGL that the data for the vertexIndex is coming in from an array
	glEnableVertexAttribArray(s_vertexIndex);
	//bind the buffer with data.
	//the moment this buffer is bound instead of 0, the last param of glVertexAttribPointer
	//is interpreted as an offset and not a pointer
	glBindBuffer(GL_ARRAY_BUFFER, s_vertexBufferId);
	//send the data for this index to OpenGL, specifying it's format and structure
	//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
	glVertexAttribPointer(s_vertexIndex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//tell OpenGL that the data for the vertexIndex/colorIndex is coming in from an array
	glEnableVertexAttribArray(s_uvIndex);
	//bind the buffer with data.
	//the moment this buffer is bound instead of 0, the last param of glVertexAttribPointer
	//is interpreted as an offset and not a pointer
	glBindBuffer(GL_ARRAY_BUFFER, s_uvsBufferId);
	//send the data for this index to OpenGL, specifying it's format and structure
	//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
	glVertexAttribPointer(s_uvIndex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, m_texture.GetId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(s_diffuseTextureIndex, 0);

	//Draws elements from each enabled array using the specified mode (which is default for Unity etc as well)
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(s_vertexIndex);
	glDisableVertexAttribArray(s_uvIndex);
}
