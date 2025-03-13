#pragma once
#include "Enemy.hpp"
#include "Timer.hpp"
#include "raylib.h"
#include <vector>

// TODO: clear all enemies on new lever start (
class Spawner {
public:
	Texture2D spriteSheet;

	const int spawnDelay = 4; // in seconds
	Timer spawnTimer = Timer(spawnDelay);
	const int MAX_ENEMY_COUNT = 3;
	int enemyCount = 0;

	std::vector<Enemy*> enemies;
public:
	Spawner();

	void LoadAssets();
	void Draw();
	void Update(const Vector2& playerPos);
	void Clear();

	Vector2 RandomPos();
	int RandomInt(const int& maxInt);
};
