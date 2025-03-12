#include "Enemy.hpp"
#include <cmath>

void Enemy::Draw(const Texture2D& spriteSheet) const {
	DrawTextureRec(spriteSheet, spriteRect, position, WHITE);
}

void Enemy::Spawn(const Vector2& pos) {
	position = pos;
}

void Enemy::Update(const Vector2& playerPos){
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
}