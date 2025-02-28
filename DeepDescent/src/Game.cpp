#include "Game.hpp"
#include "raylib.h"

#include <iostream>

Game::Game(){}
Game::~Game(){}

void Game::Run()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
	SetTargetFPS(FPS);

	map.LoadAssets();
	player.LoadAssets();

	StartNewLevel(); // takes care of player and enemy spawining, map gen etc...

	while(!WindowShouldClose())
	{
		Update();
		Draw();
	}

	CloseWindow();
}

void Game::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);

	map.Draw();
	player.Draw();

	EndDrawing();
}
void Game::Update()
{
	// TEMPORARY KEY BINDING
	if(IsKeyPressed(KEY_P))
	{
		if (IsWindowFullscreen()){ SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); }
		else
		{
			int monitor = GetCurrentMonitor();
			SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
		}

		ToggleFullscreen();
		map.CalculateOffset();
	}

	player.Update();

	if (IsKeyPressed(KEY_SPACE))
		StartNewLevel();
}

void Game::StartNewLevel()
{
	map.Generate();
	const auto spawnPos = map.GetEmptyTile();

	player.Spawn(spawnPos);
}
