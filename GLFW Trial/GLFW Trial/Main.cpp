//GLFW is used in the code, since GLEW is already including OpenGl we dont need GLFW to do it
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>

#include "ShaderUtil.h"

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
	GLuint programID = ShaderUtil::createProgram("vertexshader.vs", "fragmentshader.fs");

	//declare the data to upload
	const GLfloat vertices[] = {
		//1 triangle, 3 vertices per triangle, 3 floats per vertex = 9 floats in total
		-0.5f, -0.5f, 0,
		0.5f, -0.5f, 0,
		-0.5f, 0.5f, 0
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

	const GLfloat colors[]{
		//1 triangle, 3 vertices per triangle, 1 color per vertex, 3 "floats" per color RGB = 9 floats in total
		1,0,0,
		0,1,0,
		0,0,1
	};

	//create a handle to the buffer
	GLuint colorBufferId;
	glGenBuffers(1, &colorBufferId);
	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex color data will be created
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
	//stream all our data to the array buffer endpoint to which our vertexColorsBufferId is connected
	//note that vertexColorsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

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

		//get index for the attributes in the shader
		GLint vertexIndex = glGetAttribLocation(programID, "vertex");
		GLint colorIndex = glGetAttribLocation(programID, "color");

		//tell OpenGL that the data for the vertexIndex/colorIndex is coming in from an array
		glEnableVertexAttribArray(vertexIndex);
		glEnableVertexAttribArray(colorIndex);

		//bind the buffer with data.
		//the moment this buffer is bound instead of 0, the last param of glVertexAttribPointer
		//is interpreted as an offset and not a pointer
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
		//send the data for this index to OpenGL, specifying it's format and structure
		//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
		glVertexAttribPointer(vertexIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//send the data for this index to OpenGL, specifying it's format and structure
		//colorIndex // 3 bytes per element // floats // don't normalize // the data itself
		glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
		glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//Draws elements from each enabled array using the specified mode (which is default for Unity etc as well)
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(vertexIndex);
		glDisableVertexAttribArray(colorIndex);

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