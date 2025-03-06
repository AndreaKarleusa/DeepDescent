#pragma once
#include "raylib.h"
#include "Settings.hpp"
#include "Map.hpp"
#include "Player.hpp"

#include <vector>

class Game
{
public:
	Camera2D camera;
	Map map;
	Player player;
public:
	Game();
	~Game();

	void Run();
	void Draw();
	void Update();
	void LoadAssets();
	void CameraSetup();

	void StartNewLevel();
	std::vector<Tile> CollisonTiles();
};