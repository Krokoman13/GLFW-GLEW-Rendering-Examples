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

Window::Window(const char* a_title, unsigned int a_width, unsigned int a_height): 
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

	//Enable vertical synchronization
	glfwSwapInterval(1);

	//Initialize GLEW to manage OpenGL extensions
	err = glewInit();
	if (err != GLEW_OK)
	{
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
		a_toRender.front()->Display(camera);
		a_toRender.pop();
	}

	//Swap the front and back buffers
	glfwSwapBuffers(m_pWindow);

	//Poll for and process events
	glfwPollEvents();
}
