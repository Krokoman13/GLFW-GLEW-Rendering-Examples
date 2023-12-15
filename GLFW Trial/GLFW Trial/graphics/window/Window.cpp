#include "Window.hpp"

void error_callback(int a_error, const char* a_description)
{
	//Print the error description to the standard error output
	std::cerr << "GLFW Error, " << a_error << ": " << a_description << std::endl;
}

//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
//}

Window::Window(const char* a_title, const unsigned int a_width, const unsigned int a_height, const bool a_hasVsync):
	camera(a_width, a_height), m_width(a_width), m_height(a_height)
{
	//Initialize GLFW
	if (!glfwInit())
	{
		throw std::runtime_error("Failed to Initialize GLFW");
	}

	//Set the error callback function to be called whenever an error occurs in GLFW
	glfwSetErrorCallback(error_callback);

	//Set the required OpenGL context version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	m_pWindow = glfwCreateWindow(a_width, a_height, a_title, NULL, NULL);
	if (!m_pWindow)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	//glfwSetKeyCallback(m_pWindow, key_callback);

	//Make the created window the current context
	glfwMakeContextCurrent(m_pWindow);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "glfwMakeContextCurrent failed with error: " << err << std::endl;
	}

	//Set vertical synchronization
	SetVSync(a_hasVsync);

	//Initialize GLEW to manage OpenGL extensions
	err = glewInit();
	if (err != GLEW_OK)
	{
		char* error = (char*)glewGetErrorString(err);
		std::cerr << "GLEW INIT FAIL: " << error << std::endl;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0, 0, 0, 1);
}

Window::~Window()
{
	//Destroy the window and terminate GLFW
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

void Window::SetVSync(const bool a_hasVsync)
{
	glfwSwapInterval(a_hasVsync ? 1 : 0);
}

bool Window::IsOpen()
{
	return !glfwWindowShouldClose(m_pWindow);
}

void Window::Draw(const Renderable* a_toRender)
{
	a_toRender->Display(camera);
}

void Window::Draw(const std::vector<Renderable*>& a_toRender)
{
	for (auto it : a_toRender)
	{
		Draw(it);
	}
}

void Window::Display()
{
	//Swap the front and back buffers
	glfwSwapBuffers(m_pWindow);

	//Poll for and process events
	glfwPollEvents();
}

void Window::Clear()
{
	//Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
}
