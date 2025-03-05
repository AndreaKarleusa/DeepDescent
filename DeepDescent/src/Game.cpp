#include "Game.hpp"
#include "raylib.h"

#include <iostream>

Game::Game(){}
Game::~Game(){}

void Game::Run()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
	SetTargetFPS(FPS);
	CameraSetup();
	LoadAssets();

	StartNewLevel();

	while(!WindowShouldClose())
	{
		Update();
		Draw();
	}

	CloseWindow();
}

void Game::LoadAssets()
{
	map.LoadAssets();
	player.LoadAssets();
}

void Game::CameraSetup()
{
	camera.offset = {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2};
	camera.target = {MAP_SIZE*TILE_SIZE/2, MAP_SIZE*TILE_SIZE/2};
	camera.zoom = 1.0f;
	camera.rotation = 0.0f;
}

void Game::Draw()
{
	BeginDrawing();
	BeginMode2D(camera);

		ClearBackground(BLACK);
		map.Draw();
		player.Draw();

	EndMode2D();
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
		camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	}

	player.Update();

	if (IsKeyPressed(KEY_SPACE))
		StartNewLevel();
}

void Game::StartNewLevel()
{
	map.Generate();
	const Vector2 spawnPos = map.GetEmptyTile();
	player.Spawn(spawnPos);
}
