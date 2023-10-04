//GLFW is used in the code, since GLEW is already including OpenGl we dont need GLFW to do it
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>

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


	//define the source for the shader as a pointer to an array of char
	const GLchar* vertexShaderSource = R"(
        #version 330

        in vec3 vertex;
        in vec3 color;

        out vec3 fColor;

        void main ()
        {
            gl_Position = vec4(vertex,1);
            fColor = color;
        }
    )";


	//create a vertex shader
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	//load shader source onto GPU: we only have 1 bit of source to load, which is null terminated
	glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);

	//compile shader ON GPU
	GLint success;
	GLchar infoLog[512];
	glCompileShader(vertexShaderID);
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//define the source for the shader as a pointer to an array of char
	const GLchar* fragmentShaderSource = R"(
        #version 330

        in vec3 fColor;
        out vec4 sColor;

        void main ()
        {
            sColor = vec4(fColor, 1);
        }
    )";

	//create a fragment shader
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	//load shader source onto GPU: we only have 1 bit of source to load, which is null terminated
	glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
	//compile shader ON GPU, without error checking for now for brevity
	GLint success;
	GLchar infoLog[512];
	glCompileShader(vertexShaderID);
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//first create the program ID
	GLuint programID = glCreateProgram();
	//now attach the shaders to the program and link
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	GLint success;
	GLchar infoLog[512];
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//since the vertex and fragment shaders are linked to the program we can delete them
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	//declare the data to upload
	const GLfloat vertices[] = {
		//1 triangle, 3 vertices per triangle, 3 floats per vertex = 9 floats in total
		-0.5f, -0.5f, 0,
		0.5f, -0.5f, 0,
		-0.5f, 0.5f, 0
	};

	const GLfloat colors[]{
		//1 triangle, 3 vertices per triangle, 1 color per vertex, 3 "floats" per color RGB = 9 floats in total
		1,0,0,
		0,1,0,
		0,0,1
	};

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

		//get index for the different attributes in the shader
		GLint vertexIndex = glGetAttribLocation(programID, "vertex");
		GLint colorIndex = glGetAttribLocation(programID, "color");

		//tell OpenGL that the data for the vertexIndex/colorIndex is coming in from an array
		glEnableVertexAttribArray(vertexIndex);
		glEnableVertexAttribArray(colorIndex);

		//send the data for this index to OpenGL, specifying it's format and structure
		//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
		glVertexAttribPointer(vertexIndex, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		//colorIndex // 3 bytes per element // floats // don't normalize // the data itself
		glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, colors);

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