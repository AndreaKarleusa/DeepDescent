#pragma once
#include "raylib.h"
#include "Settings.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "Timer.hpp"
#include <vector>

enum Tool {
	Pickaxe,
	Shovel
};

// IDEA: gain energy/health each 10 levels ???
// TODO: make mining when you hold the mouse down (add a mining timer)
class Player
{
public:
	Texture2D playerSprite;
	Rectangle hitbox;

	Vector2 position;
	Vector2 dir;
	Vector2 vel = { 0.0f, 0.0f };
	const float MAX_VEL = 3.0f;
	const float acc = 0.6f;
	const float fr = 0.14;
	const float knockback = 2.0f;

	const int MAX_HEALTH = 5;
	const int MAX_ENERGY = 5;
	int health = MAX_HEALTH;
	int energy = MAX_ENERGY;

	Timer mercyWindow = Timer(2);
	Timer miningDelay = Timer(0.5);
	//Timer energyRecharge = Timer(0.6);

	Texture2D toolsSprite;
	Rectangle toolRects[2] = {
		{0,0, TILE_SIZE, TILE_SIZE},
		{TILE_SIZE, 0, TILE_SIZE, TILE_SIZE}
	};
	Vector2 toolPos;
	Tool tool = Pickaxe;

	const float toolRange = 2.0f*TILE_SIZE;
	const float toolKnockback = 4.0f;
	const float pickaxeDamage = 1.0f;
	const float shovelDamage= 1.0f;

	bool foundStaircase = false;

public:
	Player();
	~Player();

	void LoadAssets();
	void Draw(const Camera2D& cam);
	void Update(Tile tiles[MAP_SIZE][MAP_SIZE], 
				std::vector<Enemy*>& enemies,
				const Camera2D& cam);

	void Spawn(const Vector2& spawnPos);
	void ResetStats();
	std::vector<Tile> CheckCollision(Tile tiles[MAP_SIZE][MAP_SIZE]);
};