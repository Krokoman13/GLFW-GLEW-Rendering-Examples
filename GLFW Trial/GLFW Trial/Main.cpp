//GLFW is used in the code, since GLEW is already including OpenGl we dont need GLFW to do it
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>
#include <memory>

#include "graphics/Image.hpp"
#include "graphics/window/Window.hpp"

int main()
{
	Window window("Rendering Texture", 640, 480);

	ResourceCache<Texture> textureCache;
	Image::pTextureCache = &textureCache;

	//==============
	
	//Image* bigImage = new Image("textures/veryBig.jpg");
	//bigImage->Load();

	Image* brickImage = new Image("textures/bricks.jpg");
	brickImage->Load();

	Image* winImage = new Image("textures/windowsImage.jpg");
	winImage->SetFilterParam(GL_NEAREST, GL_NEAREST);
	winImage->Load();

	winImage->xScale = 1.f;
	winImage->yScale = 1.f;
	winImage->x = -1.f;
	winImage->y = -1.f;

	//==============

	//Main loop
	while (window.IsOpen())
	{
		//Update loop
		window.Draw(winImage);
		window.Draw(brickImage);

		window.Display();
	}

	delete brickImage;
	delete winImage;

	return 0;
}