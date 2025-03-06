#include "Player.hpp"
#include <iostream>

Player::Player() {}
Player::~Player() {}

void Player::LoadAssets()
{
	Image img = LoadImage("assets/player.png");
	playerSprite = LoadTextureFromImage(img);
	UnloadImage(img);
}

void Player::Draw()
{
	DrawTexture(playerSprite, position.x, position.y, WHITE);
}

void Player::Update()
{
	direction.x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
	direction.y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

	position.x += speed * direction.x;
	position.y += speed * direction.y;

	if (IsKeyPressed(MOUSE_BUTTON_LEFT) && playerState == State::Mining) { std::cout << "Mining!\n"; }
	else if (IsKeyPressed(MOUSE_BUTTON_LEFT) && playerState == State::Attacking) { std::cout << "Attacking!\n"; }
}

void Player::Spawn(const Vector2& spawnPos)
{
	position = spawnPos;
}