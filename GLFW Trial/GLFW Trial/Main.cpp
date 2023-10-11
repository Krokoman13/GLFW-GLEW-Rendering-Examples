//GLFW is used in the code, since GLEW is already including OpenGl we dont need GLFW to do it
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>

#include "loaders/ShaderUtil.h"
#include "loaders/Texture.hpp"

//Function to handle GLFW errors
void error_callback(int error, const char* description)
{
	//Print the error description to the standard error output
	std::cerr << "GLFW Error, " << error << ": " << description << std::endl;
}

int main()
{
	//Initialize GLFW
	if (!glfwInit())
	{
		//If initialization fails, print an error message and return -1
		std::cerr << "Failed to Initialize GLFW";
		return -1;
	}

	//Set the error callback function to be called whenever an error occurs in GLFW
	glfwSetErrorCallback(error_callback);

	//Set the required OpenGL context version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	//Create a GLFW window with the specified properties
	GLFWwindow* window = glfwCreateWindow(640, 480, "Colorfull Triangle", NULL, NULL);
	if (!window)
	{
		//If the window creation fails, print an error message and return -1
		std::cerr << "Failed to create GLFW window";
		return -1;
	}

	//Make the created window the current context
	glfwMakeContextCurrent(window);

	//Enable vertical synchronization
	glfwSwapInterval(1);

	//Initialize GLEW to manage OpenGL extensions
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		//If GLEW initialization fails, print an error message and return -1
		char* error = (char*)glewGetErrorString(err);
		std::cout << "GLEW INIT FAIL: " << error << std::endl;
		return -1;
	}

	//==============

	//Create the shader program
	GLuint programID = ShaderUtil::createProgram("texture.vert", "texture.frag");

	//declare the data to upload
	const GLfloat vertices[] = {
		//2 triangles forming a rectangle, 3 vertices per triangle, 3 floats per vertex = 12 floats in total
		-0.5f,  0.5f, 0.0f,  // Top left
		-0.5f, -0.5f, 0.0f,  // Bottom left
		0.5f,  0.5f, 0.0f,  // Top right
		0.5f, -0.5f, 0.0f,  // Bottom right
	};

	//create a handle to the buffer
	GLuint vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	//stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	//note that vertexPositionsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//get index for the attributes in the shader
	GLint vertexIndex = glGetAttribLocation(programID, "vertex");
	"textures/bricks.jpg";

	Texture texture("textures/bricks.jpg");
	texture.Load();

	GLint uDiffuseTexture = glGetUniformLocation(programID, "diffuseTexture");

	//declare the data to upload
	const GLfloat uvs[] = {
		//2 triangles, 3 vertices per triangle, 2 floats per vertex = 12 floats in total
		0.0f, 0.0f,  // Bottom left corner
		1.0f, 0.0f,  // Bottom right corner
		0.0f, 1.0f,  // Top left corner
		1.0f, 1.0f   // Top right corner
	};

	//create a handle to the buffer
	GLuint uvsBufferId;
	glGenBuffers(1, &uvsBufferId);
	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, uvsBufferId);
	//stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//get index for the attributes in the shader
	GLint uvIndex = glGetAttribLocation(programID, "uv");

	//==============

	glClearColor(0, 0, 0, 1);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//==============
		
		//Update loop
		//tell the GPU to use this program
		glUseProgram(programID);

		//tell OpenGL that the data for the vertexIndex/colorIndex is coming in from an array
		glEnableVertexAttribArray(vertexIndex);
		//bind the buffer with data.
		//the moment this buffer is bound instead of 0, the last param of glVertexAttribPointer
		//is interpreted as an offset and not a pointer
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
		//send the data for this index to OpenGL, specifying it's format and structure
		//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
		glVertexAttribPointer(vertexIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//tell OpenGL that the data for the vertexIndex/colorIndex is coming in from an array
		glEnableVertexAttribArray(uvIndex);
		//bind the buffer with data.
		//the moment this buffer is bound instead of 0, the last param of glVertexAttribPointer
		//is interpreted as an offset and not a pointer
		glBindBuffer(GL_ARRAY_BUFFER, uvsBufferId);
		//send the data for this index to OpenGL, specifying it's format and structure
		//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
		glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//setup texture slot 0
		glActiveTexture(GL_TEXTURE0);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, texture.GetId());
		//tell the shader the texture slot for the diffuse texture is slot 0
		glUniform1i(uDiffuseTexture, 0);

		//Draws elements from each enabled array using the specified mode (which is default for Unity etc as well)
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glDisableVertexAttribArray(vertexIndex);
		glDisableVertexAttribArray(uvIndex);

		//==============

		//Swap the front and back buffers
		glfwSwapBuffers(window);

		//Poll for and process events
		glfwPollEvents();
	}
	
	//Destroy shader program
	glDeleteProgram(programID);

	//Destroy the window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}