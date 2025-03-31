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
	const float acc = 70.0f;
	const float fr = 0.85f;
	float knockback = 0;

	const float moveDelay = 0.75f;
	Timer movementTimer = Timer(moveDelay);

	bool alive = true;
	const float MAX_HEALTH = 2.0f;
	float health = MAX_HEALTH;
	const float damage = 1.0f;

	float forceAmout = 0;
	Vector2 forceDirection = { 0.0f, 0.0f };
public:
	Enemy();

	void Draw(const Texture2D& spriteSheet) const;
	void Update(const float dt, const Vector2& playerPos);

	void Spawn(const Vector2& position);
	void Attack(); 
	void Damage(const float& damage);
	Vector2 GetDirection(); 

	void Knockback(const float& knockbackAmount);
	void ApplyForce(const float& amout, const Vector2& direction);
};
