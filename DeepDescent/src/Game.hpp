#pragma once
#include "raylib.h"
#include "Map.hpp"

class Game
{
private:
	const char* SCREEN_TITLE = "Deep Descent";
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 720;
	const int FPS = 60;

	Map map;
public:
	Game();
	~Game();
public:
	void Run();
	void Draw();
	void Update();
};