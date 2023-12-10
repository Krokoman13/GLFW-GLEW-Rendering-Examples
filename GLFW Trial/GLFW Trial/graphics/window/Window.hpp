#pragma once
#include <queue>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glew.h>

#include "Renderable.hpp"

void error_callback(int error, const char* description);

class Camera
{
private:
	Matrix3 m_ortho;

public:
	Matrix3 identity;

	Camera(const unsigned int a_width, const unsigned int a_height)
	{
		m_ortho.Scale(Vec2(2.f / float(a_width), -2.f / float(a_height)));
		m_ortho.Translate(-Vec2(a_width / 2.f, a_height / 2.f));
	}

	Vec2 GetSize() const { return 2.f / m_ortho.GetScale(); }

	operator Matrix3() const { return getMatrix(); }

private:
	inline Matrix3 getMatrix() const { return (Matrix3)(identity * m_ortho); }
};

class Window
{
private:
	GLFWwindow* m_pWindow;
	std::queue<Renderable*> m_toRender;

	unsigned int m_width;
	unsigned int m_height;

public:
	Window(const char* a_title, const unsigned int a_width, const unsigned int a_height);
	~Window();

	Camera camera;

public:
	bool IsOpen();
	void Draw(Renderable* a_renderable);
	void Display(std::queue<Renderable*>& a_toRender);
	void Display();
};

