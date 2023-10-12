#include "Window.hpp"

void error_callback(int a_error, const char* a_description)
{
	//Print the error description to the standard error output
	std::cerr << "GLFW Error, " << a_error << ": " << a_description << std::endl;
}

Window::Window(const char* a_title, unsigned int a_width, unsigned int a_height)
{
	//Initialize GLFW
	if (!glfwInit())
	{
		//If initialization fails, print an error message and return -1
		std::cerr << "Failed to Initialize GLFW";
	}

	//Set the error callback function to be called whenever an error occurs in GLFW
	glfwSetErrorCallback(error_callback);

	//Set the required OpenGL context version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	m_pWindow = glfwCreateWindow(a_width, a_height, a_title, NULL, NULL);
	if (!m_pWindow)
	{
		//If the window creation fails, print an error message and return -1
		std::cerr << "Failed to create GLFW window";
	}

	//Make the created window the current context
	glfwMakeContextCurrent(m_pWindow);

	//Enable vertical synchronization
	glfwSwapInterval(1);

	//Initialize GLEW to manage OpenGL extensions
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		//If GLEW initialization fails, print an error message and return -1
		char* error = (char*)glewGetErrorString(err);
		std::cout << "GLEW INIT FAIL: " << error << std::endl;
	}

	glClearColor(0, 0, 0, 1);
}

Window::~Window()
{
	//Destroy the window and terminate GLFW
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

bool Window::IsOpen()
{
	return !glfwWindowShouldClose(m_pWindow);
}

void Window::Draw(Renderable* a_renderable)
{
	m_toRender.push(a_renderable);
}

void Window::Display()
{
	Display(m_toRender);
}

void Window::Display(std::queue<Renderable*>& a_toRender)
{
	//Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	while (!a_toRender.empty()) {
		a_toRender.front()->Display();
		a_toRender.pop();
	}

	//Swap the front and back buffers
	glfwSwapBuffers(m_pWindow);

	//Poll for and process events
	glfwPollEvents();
}
