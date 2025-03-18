#pragma once
#include <raylib.h>
#include "Settings.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Spawner.hpp"

#include <vector>

class Game
{
public:
	const Color TEXT_COLOR = {246, 214, 189, 255};	
	const Color BG_COLOR = { 8, 20, 30, 255};

	Camera2D camera;
	Map map;
	Player player;
	Spawner spawner;

	bool exitGame = false;
public:
	Game();
	~Game();

	void Run();
	void Draw();
	void Update();

	void LoadAssets();
	void CameraSetup();
	void GameplayCameraSetup();
	void HandleFullscreen();

	void TitleScreen();
	void DeathScreen();
	void StartNewLevel();
};