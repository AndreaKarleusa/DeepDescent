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
	const float MAX_HEALTH = 5.0f;
	float health = MAX_HEALTH;
	const float damage = 1.0f;
public:
	Enemy();

	void Draw(const Texture2D& spriteSheet) const;
	void Update(const Vector2& playerPos);

	void Spawn(const Vector2& pos);
	void Attack(); 
	void Damage(const float& damage);
};
