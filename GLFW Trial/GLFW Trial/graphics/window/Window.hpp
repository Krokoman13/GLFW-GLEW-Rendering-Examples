#pragma once
#include <iostream>
#include <vector>

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

	unsigned int m_width;
	unsigned int m_height;

public:
	Window(const char* a_title, const unsigned int a_width, const unsigned int a_height, const bool a_hasVsync = true);
	~Window();

	Camera camera;

public:
	inline void SetVSync(const bool a_hasVsync);

	bool IsOpen();

	void Draw(const Renderable* a_toRender);
	void Draw(const std::vector<Renderable*>& a_toRender);

	void endDisplay();
	void clear();
};

