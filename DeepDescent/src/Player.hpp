#pragma once
#include "raylib.h"
#include "Settings.hpp"

enum class State
{
	Mining,
	Attacking
};

// gain energy/health each 10 levels ???
class Player
{
public:
	Texture2D textureSheet;
	Rectangle playerSprite;
	Rectangle toolSprite;
	Rectangle hitbox;

	Vector2 position;
	Vector2 direction;
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

	void Spawn(const Vector2& spawnPos);
	void LoadAssets();
	void Draw();
	void Update();
};