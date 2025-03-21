#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy() {}

void Enemy::Draw(const Texture2D& spriteSheet) const {
	DrawTextureRec(spriteSheet, spriteRect, pos, WHITE);
}

void Enemy::Spawn(const Vector2& position) {
	pos = position;
	spriteRect = {
		0, 0, TILE_SIZE, TILE_SIZE
	};
	hitbox = { pos.x, pos.y,
			   spriteRect.width, spriteRect.height
	};
	movementTimer.Start();
}

void Enemy::Update(const Vector2& playerPos){
	if (health <= 0) {
		alive = false;
		return;
	}

	if (movementTimer.Check()) {
		dir.x = playerPos.x - pos.x;
		dir.y = playerPos.y - pos.y;

		const float dirLen = sqrt(dir.x * dir.x + dir.y * dir.y);
		if (dirLen == 0)
			return;
		dir.x /= dirLen;
		dir.y /= dirLen;

		vel.x += acc * dir.x;
		vel.y += acc * dir.y;
	}

	vel.x -= fr * vel.x;
	vel.y -= fr * vel.y;

	pos.x += vel.x;
	pos.y += vel.y;

	hitbox.x = pos.x;
	hitbox.y = pos.y;
}

void Enemy::Damage(const float& damage) {
	health -= damage;
}

Vector2 Enemy::GetDirection() {
	return dir;
}

void Enemy::Knockback(const int& knockback) {
	vel.x += knockback * -dir.x;
	vel.y += knockback * -dir.y;
}