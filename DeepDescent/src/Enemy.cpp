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

void Enemy::Update(const float dt, const Vector2& playerPos){
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

		vel.x += acc * dir.x * dt;
		vel.y += acc * dir.y * dt;
	}

	vel.x -= fr * vel.x * dt;
	vel.y -= fr * vel.y * dt;

	pos.x += vel.x;
	pos.y += vel.y;

	hitbox.x = pos.x;
	hitbox.y = pos.y;
}

void Enemy::Damage(const float& dt, const float& damage) {
	health -= damage;
}

Vector2 Enemy::GetDirection() {
	return dir;
}

void Enemy::Knockback(const float dt, const float& knockback, const Vector2& knockbackDir) {
	vel.x += knockback * knockbackDir.x * dt;
	vel.y += knockback * knockbackDir.y * dt;
}