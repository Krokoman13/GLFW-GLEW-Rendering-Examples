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

#include <chrono>
#include <thread>

int main()
{
	//PathManager::ResetPaths();
	PathManager::MapPaths();

	ResourceCache<Texture, std::string> texureCache;
	ResourceCache<Shader, std::string> shaderCache;
	ResourceCache<GLBuffer, unsigned int> bufferCache;

	ResourceManager::pTexureCache = &texureCache;
	ResourceManager::pShaderCache = &shaderCache;
	ResourceManager::pGLBufferCache = &bufferCache;

	Window window("Rendering Texture", 640, 480, false);

	//==============
	//Start
	std::vector<Renderable*> sprites;
	unsigned int i = 0;
	unsigned int size = 220;
	Vec2 offset(150, 150);

	unsigned int maxColumns = 1;
	unsigned int maxRows = 1;

	//==============
	std::chrono::steady_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	//Main loop
	while (window.IsOpen())
	{
		window.clear();

		//==============
		//Update loop

		window.Draw(sprites);

		//==============

		window.endDisplay();

		if (i == maxColumns * maxRows)
		{
			std::chrono::steady_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
			std::cout << "Duration: " << ms_int << std::endl;
		}
		else if (i < maxColumns * maxRows)
		{
			Sprite* nextSprite = new Sprite(RS__BRICKS_JPG);
			nextSprite->Load();
			nextSprite->SetLocalScale(0.1f);
			nextSprite->SetLocalPosition(Vec2(size * (i % maxColumns), size * (i / maxColumns)) + offset);
			sprites.push_back(nextSprite);
		}

		i++;
	}

	//==============
	//End
	while (!sprites.empty())
	{
		delete sprites.back();
		sprites.pop_back();
	}

	//==============

	texureCache.Clear();
	shaderCache.Clear();
	bufferCache.Clear();

	return 0;
}