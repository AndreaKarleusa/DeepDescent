#include "Game.hpp"
#include <raylib.h>

#include <iostream>
#include <vector>

Game::Game(){}
Game::~Game(){}

void Game::Run()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
	SetTargetFPS(FPS);
	HideCursor();
	CameraSetup();
	LoadAssets();

	TitleScreen();

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
	spawner.LoadAssets();
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
		player.Draw(camera);
		spawner.Draw();

	EndMode2D();
	EndDrawing();
}
void Game::Update()
{
	// TEMPORARY KEY BINDING
	if(IsKeyPressed(KEY_P))
	{
		if (IsWindowFullscreen())
		{ 
			SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); 
			camera.zoom = 1.0f;
		}
		else
		{
			int monitor = GetCurrentMonitor();
			SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
			camera.zoom = 1.5f;
		}

		ToggleFullscreen();
		camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	}
	
	player.Update(map.tiles, spawner.enemies, camera);
	map.Update();
	spawner.Update(player.position);

	if (player.foundStaircase) {
		StartNewLevel();
		player.foundStaircase = false;
	}

	if (player.health <= 0) {
		DeathScreen();

		// TODO: make a reset function for the whole player
		// TODO: make the new level function reset the player HP
		player.health = player.MAX_HEALTH;
		player.energy= player.MAX_ENERGY;
	}
}

void Game::StartNewLevel()
{
	map.Generate();
	const Vector2 spawnPos = map.GetEmptyTile();
	
	player.Spawn(spawnPos);
	spawner.Clear();
}

void Game::TitleScreen() {
	while (!IsKeyPressed(KEY_SPACE)) {
		BeginDrawing();
		ClearBackground(BLACK);
			DrawText("DEEP DESCENT", 0, 0, 50, RAYWHITE);
			DrawText("press <space> to start", 0, 50, 40, RAYWHITE);
			DrawText("press <esc> to quit exit", 0, 90, 40, RAYWHITE);
		EndDrawing();

		// TODO: currently not working
		if (WindowShouldClose())
			CloseWindow();

	}
}

void Game::DeathScreen() {
	while (!IsKeyPressed(KEY_SPACE)) {
		BeginDrawing();
			ClearBackground(BLACK);
			DrawText("GAME OVER!", 0, 0, 50, RAYWHITE);
			DrawText("press <space> to start again", 0, 50, 40, RAYWHITE);
			DrawText("press <esc> to quit game", 0, 90, 40, RAYWHITE);
		EndDrawing();

		// TODO: currently not working
		if (WindowShouldClose())
			CloseWindow();

	}
	StartNewLevel();
}