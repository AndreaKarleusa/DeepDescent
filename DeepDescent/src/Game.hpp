#pragma once
#include "raylib.h"
#include "Settings.hpp"
#include "Map.hpp"
#include "Player.hpp"

class Game
{
public:
	Map map;
	Player player;
public:
	Game();
	~Game();

	void Run();
	void Draw();
	void Update();

	/*
		- generates map
		- spawns player
		- spawns enemies
		- spawns exit
	*/
	void StartNewLevel();
};