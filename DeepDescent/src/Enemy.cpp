#include "Enemy.hpp"

void Enemy::Draw(const Texture2D& spriteSheet) const {
	DrawTextureRec(spriteSheet, spriteRect, position, WHITE);
}

void Enemy::Spawn(const Vector2& pos) {
	position = pos;
}

void Enemy::Update(const Vector2& playerPos){}