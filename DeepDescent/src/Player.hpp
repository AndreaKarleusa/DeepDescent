#pragma once
#include "raylib.h"
#include "Settings.hpp"
#include "Map.hpp"
#include <vector>

enum State{
	Mining,
	Attacking
};

// gain energy/health each 10 levels ???
class Player
{
public:
	Texture2D playerSprite;
	Texture2D toolsSprite;
	Rectangle toolRect;

	Vector2 position;
	Vector2 direction;
	Vector2 velocity;
	const float speed = 3.0f;

	const int MAX_HEALTH = 15;
	const int MAX_ENERGY = 3;
	int health = MAX_HEALTH;
	int energy = MAX_ENERGY;

	Vector2 mousePos;
	State playerState = Mining;
	int toolRange = 15;
	int enemyDamage = 4;
	int blockDamage = 1;

	bool foundStaircase = false;

public:
	Player();
	~Player();

	void LoadAssets();
	void Draw();
	void Update(Tile tiles[MAP_SIZE][MAP_SIZE], const Camera2D& cam);

	void Spawn(const Vector2& spawnPos);
	std::vector<Tile> CheckCollision(Tile tiles[MAP_SIZE][MAP_SIZE]);
};