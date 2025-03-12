#pragma once
#include "Settings.hpp"
#include <raylib.h>

class Enemy {
public:
	Rectangle spriteRect = {
		0, 0, TILE_SIZE, TILE_SIZE
	};
	Rectangle hitbox;

	Vector2 position;
	const float speed = 5.0f;

	const float MAX_HEALTH = 15.0f;
	float health = MAX_HEALTH;
public:
	Enemy() = default;

	void Draw(const Texture2D& spriteSheet) const;
	void Update(const Vector2& playerPos);

	void Spawn(const Vector2& pos);
	void Attack();
	void Damage();
};
