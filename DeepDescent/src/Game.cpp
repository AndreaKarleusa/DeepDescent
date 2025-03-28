#include "Game.hpp"
#include <raylib.h>

#include <iostream>
#include <vector>
#include <string>

Game::Game(){}
Game::~Game(){}

void Game::Run()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
	SetTargetFPS(FPS);
	LoadAssets();
	CameraSetup();

	TitleScreen();
	
	GameplayCameraSetup();
	StartNewLevel();
	HideCursor();

	while(!WindowShouldClose() && !exitGame)
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

void Game::GameplayCameraSetup() {
	camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	camera.target = { MAP_SIZE * TILE_SIZE / 2, MAP_SIZE * TILE_SIZE / 2 };
}

void Game::HandleFullscreen() {
	if (IsKeyPressed(KEY_F11))
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
}

void Game::DrawUI() {
	Vector2 screenOrigin = GetScreenToWorld2D({ 0,0 }, camera);
	std::string levelText = "LEVEL: " + std::to_string(caveLevel);
	std::string healthText = "HEALTH: " + std::to_string(player.health);

	DrawText(levelText.c_str(), screenOrigin.x + 10, screenOrigin.y, 30, WHITE);
	DrawText(healthText.c_str(), screenOrigin.x + 10, screenOrigin.y + 30, 30, RED);
}

void Game::Draw()
{
	BeginDrawing();
	BeginMode2D(camera);

		ClearBackground(BG_COLOR);
		map.Draw();
		player.Draw();
		spawner.Draw();
		DrawUI();

	EndMode2D();
	EndDrawing();
}
void Game::Update()
{
	HandleFullscreen();
	float dt = GetFrameTime();

	player.Update(dt, map.tiles, spawner.enemies, camera);
	map.Update();
	spawner.Update(dt, player.position);

	if (player.foundStaircase)
		StartNewLevel();

	if (player.health <= 0)
		DeathScreen();
}

void Game::StartNewLevel()
{
	map.Generate();
	const Vector2 spawnPos = map.GetEmptyTile();
	
	player.Spawn(spawnPos);
	player.ResetStats();
	player.foundStaircase = false;

	spawner.Clear();

	caveLevel++;
}

void Game::TitleScreen() {
	while (!IsKeyPressed(KEY_SPACE) && !exitGame) {
		HandleFullscreen();
		Vector2 screenOrigin = GetScreenToWorld2D({ 0,0 }, camera);
		Vector2 screenCenter = {
			screenOrigin.x + GetScreenWidth() / 2,
			screenOrigin.y + GetScreenHeight() / 2
		};
		camera.target = screenCenter;

		BeginDrawing();
		BeginMode2D(camera);
		ClearBackground(BG_COLOR);

			DrawText("DEEP DESCENT", 
				screenCenter.x - MeasureText("DEEP DESCENT", 50)/2,
				screenCenter.y - 50,
				50, TEXT_COLOR);
			DrawText("press <space> to start", 
				screenCenter.x - MeasureText("press <space> to start", 20) / 2,
				screenCenter.y + 20,
				20, TEXT_COLOR);
			DrawText("press <esc> to quit", 
				screenCenter.x - MeasureText("press <esc> to quit", 20) / 2,
				screenCenter.y + 45,
				20, TEXT_COLOR);

		EndMode2D();
		EndDrawing();

		if (IsKeyPressed(KEY_ESCAPE))
			exitGame = true;
	}
}
void Game::DeathScreen() {
	while (!IsKeyPressed(KEY_SPACE) && !exitGame) {
		HandleFullscreen();
		Vector2 screenOrigin = GetScreenToWorld2D({ 0,0 }, camera);
		Vector2 screenCenter = {
			screenOrigin.x + GetScreenWidth() / 2,
			screenOrigin.y + GetScreenHeight() / 2
		};
		camera.target = screenCenter;

		BeginDrawing();
		BeginMode2D(camera);
		ClearBackground(BG_COLOR);

			DrawText("GAME OVER",
				screenCenter.x - MeasureText("GAME OVER", 50) / 2,
				screenCenter.y - 50,
				50, TEXT_COLOR);
			DrawText("press <space> to restart",
				screenCenter.x - MeasureText("press <space> to restart", 20) / 2,
				screenCenter.y + 20,
				20, TEXT_COLOR);
			DrawText("press <esc> to quit",
				screenCenter.x - MeasureText("press <esc> to quit", 20) / 2,
				screenCenter.y + 45,
				20, TEXT_COLOR);

		EndMode2D();
		EndDrawing();

		if (IsKeyPressed(KEY_ESCAPE))
			exitGame = true;

	}
	GameplayCameraSetup();
	StartNewLevel();
	caveLevel = 1;
}