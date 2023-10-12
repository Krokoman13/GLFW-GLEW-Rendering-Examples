#pragma once
#include <queue>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include "Renderable.hpp"

void error_callback(int error, const char* description);

class Window
{
private:
	GLFWwindow* m_pWindow;
	std::queue<Renderable*> m_toRender;

public:
	Window(const char* a_title, unsigned int a_width, unsigned int a_height);
	~Window();

public:
	bool IsOpen();
	void Draw(Renderable* a_renderable);
	void Display(std::queue<Renderable*>& a_toRender);
	void Display();
};

