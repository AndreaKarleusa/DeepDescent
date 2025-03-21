#pragma once
#include "Settings.hpp"
#include "Timer.hpp"
#include <raylib.h>

class Enemy {
public:
	Rectangle spriteRect;
	Rectangle hitbox;

	Vector2 pos;
	Vector2 dir = { 0.0f, 0.0f };
	Vector2 vel = { 0.0f, 0.0f };
	const float acc = 1.8f;
	const float fr = 0.02f;

	const float moveDelay = 0.7f;
	Timer movementTimer = Timer(moveDelay);

	bool alive = true;
	const float MAX_HEALTH = 3.0f;
	float health = MAX_HEALTH;
	const float damage = 1.0f;
public:
	Enemy();

	void Draw(const Texture2D& spriteSheet) const;
	void Update(const Vector2& playerPos);

	void Spawn(const Vector2& position);
	void Attack(); 
	void Damage(const float& damage);
	Vector2 GetDirection();
	void Knockback(const int& knockback);
};
