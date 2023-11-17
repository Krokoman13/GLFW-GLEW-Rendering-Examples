//GLFW is used in the code, since GLEW is already including OpenGl we dont need GLFW to do it
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>
#include <memory>

#include "graphics/Sprite.hpp"
#include "graphics/window/Window.hpp"

int main()
{
	Window window("Rendering Texture", 640, 480);

	ResourceCache<Texture> textureCache;
	Sprite::pTextureCache = &textureCache;

	//==============
	
	//Image* bigImage = new Image("textures/veryBig.jpg");
	//bigImage->Load();

	Sprite* brickImage = new Sprite("textures/bricks.jpg");
	brickImage->Load();
	brickImage->SetLocalPosition(window.camera.GetSize() / 2.f);
	//brickImage->SetLocalRotation(Vec2::Deg2Rad(45));

	Sprite* winImage = new Sprite("textures/windowsImage.jpg");
	winImage->SetFilterParam(GL_NEAREST, GL_NEAREST);
	winImage->Load();

	winImage->SetLocalPosition(-1.f, -1.f);

	//==============

	//Main loop
	while (window.IsOpen())
	{
		//Update loop
		//window.Draw(winImage);
		window.Draw(brickImage);
		brickImage->identity.Rotate(0.01f);

		window.Display();
	}

	delete brickImage;
	delete winImage;

	return 0;
}