#include "Spawner.hpp"
#include "random"
#include <iostream>
#include <algorithm>
using namespace std;

Spawner::Spawner() { spawnTimer.Start(); }

void Spawner::LoadAssets() {
	Image enemiesImg = LoadImage("assets/enemies.png");
	spriteSheet = LoadTextureFromImage(enemiesImg);
	UnloadImage(enemiesImg);
}

void Spawner::Draw() {
	for (const auto& enemy : enemies)
		enemy->Draw(spriteSheet);
}

void Spawner::Update(const Vector2& playerPos) {

	if (spawnTimer.Check()) {
		int spawnCount = RandomInt(MAX_ENEMY_COUNT - enemyCount);

		for (int i = 0; i < spawnCount; i++) {
			Enemy* e = new Enemy();
			e->Spawn(RandomPos());
			enemies.push_back(e);
			enemyCount++;
		}

		int newSpawnDelay = MIN_SPAWN_DELAY + RandomInt(MAX_SPAWN_DELAY - MIN_SPAWN_DELAY);
		spawnTimer.Stop();
		spawnTimer.SetDuration(newSpawnDelay);
		spawnTimer.Start();

	}

	// TODO: there has to be a better way to write this
	for (auto i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->alive) {
			enemies[i]->Update(playerPos);
		}
		else {
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
			enemyCount--;
		}
	}
}

void Spawner::Clear() {
	for (auto i = 0; i < enemies.size(); i++) {
		delete enemies[i];
		enemies.erase(enemies.begin() + i);
	}
	spawnTimer.Stop();
	spawnTimer.Start();
}

// -1 is for the array index offset
Vector2 Spawner::RandomPos() {

	Rectangle spawnZone = spawnZones[RandomInt(4-1)];

	int x = spawnZone.x + RandomInt(spawnZone.width);
	int y = spawnZone.y + RandomInt(spawnZone.height);

	//int x = RandomInt(MAP_SIZE-1);
	//int y = RandomInt(MAP_SIZE-1);
	//return Vector2{ (float)(x*TILE_SIZE), (float)(y*TILE_SIZE) };

	return Vector2 { (float)(x), (float)(y) };
}

// TODO: remove the generator because
//		 it takes a lot of resources to
//		 make one
int Spawner::RandomInt(const int& maxInt)
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, maxInt);

	return dist(gen);
}
