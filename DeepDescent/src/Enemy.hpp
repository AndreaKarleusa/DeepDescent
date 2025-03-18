#pragma once
#include "Settings.hpp"
#include <raylib.h>

class Enemy {
public:
	Rectangle spriteRect;
	Rectangle hitbox;

	Vector2 position;
	Vector2 velocity;
	const float speed = 2.0f;

	bool alive = true;
	int MAX_HEALTH = 5;
	int health = MAX_HEALTH;
	int damage = 1;
public:
	Enemy();

	void Draw(const Texture2D& spriteSheet) const;
	void Update(const Vector2& playerPos);

	void Spawn(const Vector2& pos);
	void Attack(); 
	void Damage(const int& damage);
};
