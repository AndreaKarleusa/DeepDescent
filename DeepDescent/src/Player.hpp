#pragma once
#include "raylib.h"
#include "Settings.hpp"
#include "Map.hpp"
#include <vector>

enum class State{
	Mining,
	Attacking
};

// gain energy/health each 10 levels ???
class Player
{
public:
	Texture2D playerSprite;
	Rectangle toolSprites;

	Vector2 position;
	Vector2 direction;
	Vector2 velocity;
	const float speed = 2.5f;

	const int MAX_HEALTH = 15;
	const int MAX_ENERGY = 3;
	int health = MAX_HEALTH;
	int energy = MAX_ENERGY;

	State playerState = State::Mining;
	int enemyDamage = 4;
	int blockDamage = 1;

public:
	Player();
	~Player();

	void LoadAssets();
	void Draw();
	void Update(const Tile tiles[MAP_SIZE][MAP_SIZE]);

	void Spawn(const Vector2& spawnPos);
	std::vector<Tile> CheckCollision(const Tile tiles[MAP_SIZE][MAP_SIZE]);
};