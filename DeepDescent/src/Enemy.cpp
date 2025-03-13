#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy() {}

void Enemy::Draw(const Texture2D& spriteSheet) const {
	DrawTextureRec(spriteSheet, spriteRect, position, WHITE);
}

void Enemy::Spawn(const Vector2& pos) {
	position = pos;
	spriteRect = {
		0, 0, TILE_SIZE, TILE_SIZE
	};
	hitbox = { pos.x, pos.y,
			   spriteRect.width, spriteRect.height
	};
}

// TODO: physics
void Enemy::Update(const Vector2& playerPos){
	if (health <= 0) {
		alive = false;
		return;
	}

	// calculate distance vector
	Vector2 dir = {
		playerPos.x - position.x,
		playerPos.y - position.y
	};

	// normalize the vector
	const float length = abs(sqrt(dir.x*dir.x + dir.y*dir.y));
	if (length == 0) { return; }
	dir.x /= length;
	dir.y /= length;

	// calculate velocity and move the player
	velocity.x = dir.x * speed;
	velocity.y = dir.y * speed;

	position.x += velocity.x;
	position.y += velocity.y;

	hitbox.x = position.x;
	hitbox.y = position.y;
}

void Enemy::Damage(const int& damage) {
	health -= damage;
}