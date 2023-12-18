//GLFW is used in the code, since GLEW is already including OpenGl we dont need GLFW to do it
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glew.h>
#include <iostream>
#include <memory>

#include <chrono>
#include <thread>

#include "graphics/sprite/Sprite.hpp"
#include "graphics/animations/animationSprite/AnimationSprite.hpp"
#include "graphics/window/Window.hpp"

#include "resourceManager/PathManager.hpp"
#include "resourceManager/ResourceCache/ResourceCache.hpp"
#include "resourceManager/ResourceCache/SelfRegResourceCache.hpp"
#include "resourceManager/ResourceManager.hpp"

#include "ExtraSprites/Hologram/HologramSprite.hpp"

#include "Resources/fileIndex.hpp"

Sprite* createNewSprite(unsigned int x, unsigned int y, float size)
{
	Sprite* outp = nullptr;

	unsigned int i = rand() % 10 + 1;;
	switch (i)
	{
	case 1:
		outp = new Sprite(RS__RUNICFLOOR_PNG);
		break;

	case 2:
		outp = new Sprite(RS__LAND_JPG);
		break;

	case 3:
		outp = new Sprite(RS__WINDOWSIMAGE_JPG);
		outp->SetFilter(GL_NEAREST, GL_NEAREST);
		break;

	case 4:
		outp = new HologramSprite(RS__BRICKS_JPG);
		break;

	case 5:
		outp = new Sprite(RS__BRICKS_JPG);
		outp->diffuseColor = Color(rand() % 255, rand() % 255, rand() % 255);
		break;

	default:
		outp = new Sprite(RS__BRICKS_JPG);
		break;
	}

	outp->SetLocalPosition(x * (size + 2.f) + size, y * (size + 2.f) + size);
	outp->Load();
	outp->SetSize(Vec2(size, size));
	return outp;
}

int main()
{
	srand(time(NULL));

	//PathManager::ResetPaths();
	PathManager::MapPaths();

	ResourceCache<Texture, std::string> texureCache;
	ResourceCache<Shader, std::string> shaderCache;
	ResourceCache<GLBuffer, unsigned int> bufferCache;

	ResourceManager::pTexureCache = &texureCache;
	ResourceManager::pShaderCache = &shaderCache;
	ResourceManager::pGLBufferCache = &bufferCache;

	Window window("Rendering Texture", 640, 480);

	//==============

	AnimationSprite* walkingMan = new AnimationSprite(RS__BLANK_WALKING_PNG, 3, 4);
	walkingMan->SetFilter(GL_NEAREST, GL_NEAREST);
	walkingMan->Load();

	Animation right(
		{ AnimationFrame(3, 1.f), AnimationFrame(4, 0.3f), AnimationFrame(5, 0.3f),
		 AnimationFrame(3, 0.3f), AnimationFrame(4, 0.3f), AnimationFrame(5, 1.f) },
		[walkingMan] {walkingMan->SetCurrentAnimation("left"); }
	);
	right.frames[1].SetDuration(1.f / 3.f);
	walkingMan->AddAnimation(right, "right");

	Animation left(
		{ AnimationFrame(9, 1.f), AnimationFrame(10, 0.3f), AnimationFrame(11, 0.3f),
		AnimationFrame(9, 0.3f), AnimationFrame(10, 0.3f), AnimationFrame(11, 1.f) },
		[walkingMan] {walkingMan->SetCurrentAnimation("right"); }
	);
	left.frames[1].SetDuration(1.f / 3.f);
	walkingMan->AddAnimation(left, "left");

	walkingMan->SetCurrentAnimation("left");
	walkingMan->diffuseColor = Color::Hex(0xADD8E6);
	walkingMan->SetLocalPosition(window.camera.GetSize() / 2.f);

	//==============

	float deltaTime = 0.f;
	std::chrono::steady_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	unsigned int heightCount = 8;
	unsigned int widthCount = 12;
	float size = 50.f;
	std::vector<Renderable*> renderables;

	for (unsigned int x = 0; x < widthCount; x++) {
		for (unsigned int y = 0; y < heightCount; y++) {
			Sprite* tile = createNewSprite(x, y, size);
			renderables.push_back(tile);
		}
	}

	unsigned int i = 0;
	unsigned int columnCount = 0;

	//Main loop
	while (window.IsOpen()) {
		Vec2 translation = Vec2(1.f, 0);
		window.camera.identity.Translate(-translation);

		walkingMan->identity.Translate(translation);
		walkingMan->GetCurrentAnimation().Animate(deltaTime);
		walkingMan->Update();

		i++;

		if (i > size) {
			i = 0;
			columnCount++;

			for (unsigned int y = 0; y < heightCount; y++) {
				Renderable* tile = renderables.front();
				renderables.erase(renderables.begin());
				delete tile;

				Sprite* newTile = createNewSprite(widthCount + columnCount - 1, y, size);
				renderables.push_back(newTile);
			}
		}

		window.Clear();

		//Draw loop
		window.Draw(renderables);
		window.Draw(walkingMan);

		window.Display();

		std::chrono::steady_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		std::chrono::milliseconds ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
		deltaTime = ms_int.count() / 1000.f;
		t1 = std::chrono::high_resolution_clock::now();
	}

	delete walkingMan;

	while (!renderables.empty())
	{
		Renderable* tile = renderables.front();
		renderables.erase(renderables.begin());
		delete tile;
	}

	texureCache.Clear();
	shaderCache.Clear();
	bufferCache.Clear();

	return 0;
}

