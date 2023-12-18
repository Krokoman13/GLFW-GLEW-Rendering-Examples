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

	Window window("Rendering Texture", 640, 480);

	//==============

	Sprite* brickImage = new HologramSprite(RS__BRICKS_JPG);
	brickImage->Load();
	brickImage->SetLocalPosition(window.camera.GetSize() / 2.f);

	Sprite* winImage = new Sprite(RS__WINDOWSIMAGE_JPG);
	winImage->SetFilter(GL_NEAREST, GL_NEAREST);
	winImage->Load();

	AnimationSprite* walkingMan = new AnimationSprite(RS__BLANK_WALKING_PNG, 3, 4);
	walkingMan->SetFilter(GL_NEAREST, GL_NEAREST);
	walkingMan->Load();

	Animation right(
		{AnimationFrame(3, 1.f), AnimationFrame(4, 0.3f), AnimationFrame(5, 0.3f), 
		 AnimationFrame(3, 0.3f), AnimationFrame(4, 0.3f), AnimationFrame(5, 1.f) },
		[walkingMan] {walkingMan->SetCurrentAnimation("left"); }
	);
	right.frames[1].SetDuration(1.f / 3.f);
	walkingMan->AddAnimation(right, "right");

	Animation left(
		{AnimationFrame(9, 1.f), AnimationFrame(10, 0.3f), AnimationFrame(11, 0.3f), 
		AnimationFrame(9, 0.3f), AnimationFrame(10, 0.3f), AnimationFrame(11, 1.f)},
		[walkingMan] {walkingMan->SetCurrentAnimation("right"); }
	);
	left.frames[1].SetDuration(1.f / 3.f);
	walkingMan->AddAnimation(left, "left");

	walkingMan->SetCurrentAnimation("left");
	walkingMan->diffuseColor = Color::Hex(0xADD8E6);
	walkingMan->SetLocalPosition(100, 100);

	AnimationSprite* walkingMan2 = new AnimationSprite(RS__BLANK_WALKING_PNG, 3, 4);
	walkingMan2->Load();
	walkingMan2->GetCurrentAnimation().speed = 0.1f;
	walkingMan2->diffuseColor = Color::Hex(0xFF7F7F);
	walkingMan2->SetLocalPosition(500, 100);

	//brickImage->SetLocalPosition(Vec2(1, 1));

	winImage->SetParent(brickImage);
	winImage->SetLocalPosition(100, 100);
	winImage->SetLocalScale(10.f);

	//==============

	float deltaTime = 0.f;
	std::chrono::steady_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	//Main loop
	while (window.IsOpen())
	{
		//Udate loop
		brickImage->identity.Rotate(0.01f);
		winImage->SetGlobalRotation(0);
		walkingMan->GetCurrentAnimation().Animate(deltaTime);
		walkingMan2->GetCurrentAnimation().Animate(deltaTime);
		walkingMan->Update();
		walkingMan2->Update();

		window.Clear();

		//Draw loop
		window.Draw(brickImage);
		window.Draw(winImage);
		window.Draw(walkingMan);
		window.Draw(walkingMan2);

		window.Display();

		std::chrono::steady_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		std::chrono::milliseconds ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
		deltaTime = ms_int.count() / 1000.f;
		t1 = std::chrono::high_resolution_clock::now();
	}

	delete brickImage;
	delete winImage;
	delete walkingMan;
	delete walkingMan2;

	texureCache.Clear();
	shaderCache.Clear();

	return 0;
}