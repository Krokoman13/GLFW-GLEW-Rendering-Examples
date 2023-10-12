//GLFW is used in the code, since GLEW is already including OpenGl we dont need GLFW to do it
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>

#include "graphics/Image.hpp"

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
	GLFWwindow* window = glfwCreateWindow(640, 480, "Rendering Texture", NULL, NULL);
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
	
	Image image("textures/bricks.jpg");
	image.Load();

	//==============

	glClearColor(0, 0, 0, 1);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//==============
		
		//Update loop
		image.Display();

		//==============

		//Swap the front and back buffers
		glfwSwapBuffers(window);

		//Poll for and process events
		glfwPollEvents();
	}

	//Destroy the window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}