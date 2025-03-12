#include "Spawner.hpp"
#include "random"
#include <iostream>
using namespace std;

Spawner::Spawner() { spawnTimer.Start(); }

void Spawner::LoadAssets() {
	Image enemiesImg = LoadImage("assets/enemies.png");
	spriteSheet = LoadTextureFromImage(enemiesImg);
	UnloadImage(enemiesImg);
}

void Spawner::Draw() {
	for (const auto& enemy : enemies)
		enemy.Draw(spriteSheet);
}

void Spawner::Update(const Vector2& playerPos) {

	if (spawnTimer.Check()) {
		Enemy e = Enemy();
		e.Spawn(RandomPos());
		enemies.push_back(e);
	}

	for (auto& enemy : enemies)
		enemy.Update(playerPos);
}

// -1 is for the array index offset
Vector2 Spawner::RandomPos() {
	int x = RandomInt(MAP_SIZE-1);
	int y = RandomInt(MAP_SIZE-1);

	return Vector2{ (float)(x*TILE_SIZE), (float)(y*TILE_SIZE) };
}

int Spawner::RandomInt(const int& maxInt)
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, maxInt);

	return dist(gen);
}
