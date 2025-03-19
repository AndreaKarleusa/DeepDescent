#pragma once
#include "Enemy.hpp"
#include "Timer.hpp"
#include "raylib.h"
#include <vector>

// TODO: clear all enemies on new lever start (
// TODO: make spawning in whaves
class Spawner {
public:
	Texture2D spriteSheet;

	const float MIN_SPAWN_DELAY = 2.5f;
	const float MAX_SPAWN_DELAY = 5.0f;
	Timer spawnTimer = Timer(5.0f);
	
	std::vector<Enemy*> enemies;
	const int MAX_ENEMY_COUNT = 4;
	int enemyCount = 0;

	// going from the top of the map 
	// in a clock wise direction
	Rectangle spawnZones[4] = {
		{0, -TILE_SIZE, TILE_SIZE * MAP_SIZE, TILE_SIZE},		  // top
		{TILE_SIZE*MAP_SIZE, 0, TILE_SIZE, TILE_SIZE * MAP_SIZE}, // right
		{0, TILE_SIZE*MAP_SIZE, TILE_SIZE * MAP_SIZE, TILE_SIZE}, // bottom
		{-TILE_SIZE, 0, TILE_SIZE, TILE_SIZE*MAP_SIZE},			  // left
	};

public:
	Spawner();

	void LoadAssets();
	void Draw();
	void Update(const Vector2& playerPos);
	void Clear();

	Vector2 RandomPos();
	int RandomInt(const int& maxInt);
};
