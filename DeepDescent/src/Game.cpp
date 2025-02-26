#include "Game.hpp"
#include "raylib.h"

#include <iostream>

Game::Game()
{
	std::cout << "Game has started!\n";
}
Game::~Game()
{
	std::cout << "Game has ended!\n";
}

void Game::Run()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
	SetTargetFPS(FPS);

	map.LoadAssets();

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

	EndDrawing();
}
void Game::Update()
{
	// Screen resizing - TEMPORARY KEY BINDING
	if(IsKeyPressed(KEY_P))
	{
		int monitor = GetCurrentMonitor();

		if (IsWindowFullscreen())
		{
			SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		else
		{
			SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
		}

		ToggleFullscreen();
	}

	if (IsKeyPressed(KEY_SPACE))
		map.Generate();
}
