#include "Spawner.hpp"
#include "random"
#include <iostream>
#include <algorithm>
using namespace std;

Spawner::Spawner() { 
	spawnTimer.Start();
	markerManager.SetColor({ 195, 163, 138, 255 });
}

void Spawner::LoadAssets() {
	Image enemiesImg = LoadImage("assets/enemies.png");
	spriteSheet = LoadTextureFromImage(enemiesImg);
	UnloadImage(enemiesImg);
}

void Spawner::Draw() {
	for (const auto& enemy : enemies)
		enemy->Draw(spriteSheet);

	markerManager.Draw();
}

void Spawner::Update(const float dt, const Vector2& playerPos) {

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
			enemies[i]->Update(dt, playerPos);
		}
		else {
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
			enemyCount--;
		}
	}

	for (int i = 0; i < enemies.size(); i++) {
		for (int j = 0; j < enemies.size(); j++) {
			auto& enemy1 = enemies[i];
			auto& enemy2 = enemies[j];


			if (enemies[i] == enemies[j])
				continue;

			if (CheckCollisionCircles(enemy1->hitbox.pos, enemy1->hitbox.r, enemy2->hitbox.pos, enemy2->hitbox.r)) {

				const Vector2 knockbackDir = {enemies[i]->pos.x - enemies[j]->pos.x,
											  enemies[i]->pos.y - enemies[j]->pos.y, };

				enemies[i]->ApplyForce(enemyKnockback, knockbackDir);
			}
		}

	}

	markerManager.Update(dt);

}

void Spawner::Clear() {
	for (auto& e : enemies) {
		enemyCount--;
		delete e;
	}
	enemies.clear();

	spawnTimer.Reset();
	spawnTimer.Start();
}

// -1 is for the array index offset
Vector2 Spawner::RandomPos() {

	Rectangle spawnZone = spawnZones[RandomInt(4-1)];

	int x = spawnZone.x + RandomInt(spawnZone.width);
	int y = spawnZone.y + RandomInt(spawnZone.height);

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
