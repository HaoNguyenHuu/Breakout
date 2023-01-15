#pragma once

#include<glad/glad.h>
#include"GLFW/glfw3.h"

enum  GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game 
{
public:
	//game state
	GameState State;
	bool keys[1024];
	unsigned int Width, Height;
	// constructor/destructor
	Game(unsigned int width, unsigned int height);
	~Game();
	//initailize game state(load all shaders/textures/levels)
	void Init();
	//game loop
	void ProcessInput(float dt);
	void update(float dt);
	void Render();
};