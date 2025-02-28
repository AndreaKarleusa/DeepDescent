#include "Player.hpp"
#include <iostream>

Player::Player() {}
Player::~Player() {}

void Player::LoadAssets()
{
	Image spriteSheet = LoadImage("assets/Spritesheet512.png");

	textureSheet = LoadTextureFromImage(spriteSheet);
	playerSprite = { TILE_SIZE * 3, TILE_SIZE * 2, TILE_SIZE, TILE_SIZE };

	UnloadImage(spriteSheet);
}

void Player::Draw()
{
	DrawTextureRec(textureSheet, playerSprite, position, WHITE);
}

void Player::Update()
{
	direction.x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
	direction.y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

	position.x += speed * direction.x;
	position.y += speed * direction.y;

	if (IsKeyPressed(MOUSE_BUTTON_LEFT) && playerState == State::Mining) { std::cout << "Mining!\n"; }
	if (IsKeyPressed(MOUSE_BUTTON_LEFT) && playerState == State::Attacking) { std::cout << "Attacking!\n"; }
}

void Player::Spawn(const Vector2& spawnPos)
{
	position = spawnPos;
}