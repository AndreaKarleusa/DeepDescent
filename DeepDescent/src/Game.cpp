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

	DrawRectangle(100, 100, 100, 100, RED);

	EndDrawing();
}
void Game::Update()
{
	// Fullscreen
	if(IsKeyPressed(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER))
	{
		int Monitor = GetCurrentMonitor();

		if (IsWindowFullscreen())
			SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		else
			SetWindowSize(GetMonitorWidth(Monitor), GetMonitorHeight(Monitor));

		ToggleFullscreen();
	}
}