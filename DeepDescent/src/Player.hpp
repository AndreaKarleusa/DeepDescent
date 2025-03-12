#pragma once
#include "raylib.h"
#include "Settings.hpp"
#include "Map.hpp"
#include <vector>

enum Tool {
	Pickaxe,
	Shovel
};

// gain energy/health each 10 levels ???
class Player
{
public:
	Texture2D playerSprite;

	Vector2 position;
	Vector2 direction;
	Vector2 velocity;
	const float speed = 3.0f;

	const int MAX_HEALTH = 15;
	const int MAX_ENERGY = 3;
	int health = MAX_HEALTH;
	int energy = MAX_ENERGY;

	Texture2D toolsSprite;
	Rectangle toolRects[2] = {
		{0,0, TILE_SIZE, TILE_SIZE},
		{TILE_SIZE, 0, TILE_SIZE, TILE_SIZE}
	};
	Vector2 toolPos;
	Tool tool = Pickaxe;

	int toolRange = 1.5*TILE_SIZE;
	int pickaxeDamage = 1;
	int shovelDamage= 5;

	bool foundStaircase = false;

public:
	Player();
	~Player();

	void LoadAssets();
	void Draw(const Camera2D& cam);
	void Update(Tile tiles[MAP_SIZE][MAP_SIZE], const Camera2D& cam);

	void Spawn(const Vector2& spawnPos);
	std::vector<Tile> CheckCollision(Tile tiles[MAP_SIZE][MAP_SIZE]);
};