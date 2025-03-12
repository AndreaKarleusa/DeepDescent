#pragma once
#include "Enemy.hpp"
#include "Timer.hpp"
#include "raylib.h"
#include <vector>

class Spawner {
public:
	Texture2D spriteSheet;

	const int spawnDelay = 5; // in seconds
	Timer spawnTimer = Timer(spawnDelay);

	std::vector<Enemy> enemies;
public:
	Spawner();
	~Spawner() = default;

	void LoadAssets();
	void Draw();
	void Update(const Vector2& playerPos);
	
	Vector2 RandomPos();
	int RandomInt(const int& maxInt);
};
