//GLFW is used in the code, since GLEW is already including OpenGl we dont need GLFW to do it
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glew.h>
#include <iostream>
#include <memory>

#include "graphics/sprite/Sprite.hpp"
#include "graphics/window/Window.hpp"

#include "resourceManager/PathManager.hpp"
#include "resourceManager/ResourceCache/ResourceCache.hpp"
#include "resourceManager/ResourceCache/SelfRegResourceCache.hpp"
#include "resourceManager/ResourceManager.hpp"

#include "Resources/fileIndex.hpp"

int main()
{
	//PathManager::ResetPaths();
	PathManager::MapPaths();

	SelfRegResourceCache<Texture, std::string> texureCache;
	ResourceCache<Shader, std::string> shaderCache;
	ResourceCache<GLBuffer, unsigned int> bufferCache;

	ResourceManager::pTexureCache = &texureCache;
	ResourceManager::pShaderCache = &shaderCache;
	ResourceManager::pGLBufferCache = &bufferCache;

	Window window("Rendering Texture", 640, 480);

	//==============

	{
		Sprite* brickImage = new Sprite(RS__BRICKS_JPG);
		brickImage->Load();
		brickImage->SetLocalPosition(window.camera.GetSize() / 2.f);
		delete brickImage;
	}

	Sprite* brickImage = new Sprite(RS__BRICKS_JPG);
	brickImage->Load();
	brickImage->SetLocalPosition(window.camera.GetSize() / 2.f);
	brickImage->diffuseColor = Color::Hex(0xADD8E6);

	Sprite* winImage = new Sprite(RS__WINDOWSIMAGE_JPG);
	winImage->SetFilter(GL_NEAREST, GL_NEAREST);
	winImage->Load();


	//brickImage->SetLocalPosition(Vec2(1, 1));

	winImage->SetParent(brickImage);
	winImage->SetLocalPosition(100, 100);
	winImage->SetLocalScale(10.f);

	//==============

	//Main loop
	while (window.IsOpen())
	{
		window.Clear();

		//Update loop
		window.Draw(brickImage);
		window.Draw(winImage);
		brickImage->identity.Rotate(0.01f);
		winImage->SetGlobalRotation(0);

		window.Display();
	}

	delete brickImage;
	delete winImage;

	texureCache.Clear();
	shaderCache.Clear();

	return 0;
}