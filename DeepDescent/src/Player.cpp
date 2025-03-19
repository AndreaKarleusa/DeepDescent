#include "Player.hpp"
#include "Map.hpp"

#include<raylib.h>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

Player::Player() {}
Player::~Player() {}

void Player::LoadAssets()
{
	Image playerImg = LoadImage("assets/player.png");
	Image toolsImg = LoadImage("assets/tools.png");

	playerSprite = LoadTextureFromImage(playerImg);
	toolsSprite = LoadTextureFromImage(toolsImg);

	UnloadImage(playerImg);
	UnloadImage(toolsImg);
}

// IDEA: use raylib build in TextFormat function
void Player::Draw(const Camera2D& cam)
{
	DrawTexture(playerSprite, position.x, position.y, WHITE);
	DrawTextureRec(toolsSprite, toolRects[tool], toolPos, WHITE);

	std::string healthText = "HEALTH: " + std::to_string(health);
	std::string energyText = "ENERGY: " + std::to_string(energy);
	Vector2 screenOrigin = GetScreenToWorld2D({ 0,0 }, cam);

	DrawText(healthText.c_str(), screenOrigin.x, screenOrigin.y, 25, RED);
	DrawText(energyText.c_str(), screenOrigin.x, screenOrigin.y + 25, 25, YELLOW);
}

void Player::Update(Tile tiles[MAP_SIZE][MAP_SIZE], std::vector<Enemy*>& enemies, const Camera2D& cam)
{
	// player movement
	direction.x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
	direction.y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
	velocity.x = speed * direction.x;
	velocity.y = speed * direction.y;
	
	// move and collide in the x axis
	position.x += velocity.x;
	std::vector<Tile> collisionTiles = CheckCollision(tiles);
	for (const auto& tile : collisionTiles){
		if (velocity.x > 0) { position.x = tile.collisionRec.x - playerSprite.width; }
		else if (velocity.x < 0) { position.x = tile.collisionRec.x + TILE_SIZE; }
	}

	// move and collide in the y axis
	position.y += velocity.y;
	collisionTiles = CheckCollision(tiles);
	for (const auto& tile : collisionTiles){
		if (velocity.y > 0) { position.y = tile.collisionRec.y - playerSprite.height; }
		else if (velocity.y < 0) { position.y = tile.collisionRec.y + TILE_SIZE; }
	}

	// out of bounds collision
	if (position.x <= 0) { position.x = 0; }
	if (position.x >= MAP_SIZE * TILE_SIZE - playerSprite.width) { position.x = MAP_SIZE * TILE_SIZE - playerSprite.width; }

	if (position.y <= 0) { position.y = 0; }
	if (position.y >= MAP_SIZE * TILE_SIZE - playerSprite.height) { position.y = MAP_SIZE * TILE_SIZE - playerSprite.height; }

	// tool logic
	Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), cam);
	toolPos.x = mousePos.x - TILE_SIZE / 2;
	toolPos.y = mousePos.y - TILE_SIZE / 2;

	// TODO: better variable names
	// IDEA: just put a bounding box around the player and
	//		 if the mouse point collides with it it is in range
	//       (maybe cleaner and faster)
	Vector2 mouseDistVec = {
		mousePos.x - (position.x + playerSprite.width / 2),
		mousePos.y - (position.y + playerSprite.height / 2)
	};
	int mouseDist = abs(sqrt(mouseDistVec.x*mouseDistVec.x + mouseDistVec.y*mouseDistVec.y));

	hitbox = { position.x, position.y, (float)playerSprite.width, (float)playerSprite.height };

	// IDEA: clamp the actuall mouseDist float to the toolRange

	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
		tool = (Tool)(!tool);

	// IDEA: only mine when mouse button is down
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && mouseDist <= toolRange && energy > 0){
		//energy--;
		//energyRecharge.Start();

		if (tool == Pickaxe) {
			int x = mousePos.x / TILE_SIZE;
			int y = mousePos.y / TILE_SIZE;

			if (!tiles[y][x].isEmpty)
				tiles[y][x].Damage(pickaxeDamage);
		}
		else {
			for (auto& enemy : enemies) {
				if (CheckCollisionPointRec(mousePos, enemy->hitbox)) {
					enemy->Damage(shovelDamage);
				}
			}
		}
	}


	// IDEA: make the energy a total amount (100)
	//		 and make enemies drop some of it on 
	//		 death
	/* 
	if (energyRecharge.Check()) {
		energy++;
		if (energy == MAX_ENERGY)
			energyRecharge.Stop();
	}*/

	for (auto& enemy : enemies) {
		if (CheckCollisionRecs(hitbox, enemy->hitbox) && !mercyWindow.running) {
			health -= enemy->damage;
			mercyWindow.Start();
		}
	}
	if (mercyWindow.Check()) { mercyWindow.Stop(); }
}

void Player::Spawn(const Vector2& spawnPos)
{
	position = spawnPos;
}

void Player::ResetStats() {
	health = MAX_HEALTH;
	energy = MAX_ENERGY;
}

// OPTIMIZATION:
// + use iterators to clean up the code
std::vector<Tile> Player::CheckCollision(Tile tiles[MAP_SIZE][MAP_SIZE])
{
	int x = floor(position.x / TILE_SIZE);
	int y = floor(position.y / TILE_SIZE);
	int checks = 0;
	// TODO: clean up this hitbox code
	std::vector<Tile> collisionTiles;
	hitbox = { position.x, position.y, (float)playerSprite.width, (float)playerSprite.height };

	for (int i = -1; i <= 1; i++) {
	for (int j = -1; j <= 1; j++) {
		if (y+i >= MAP_SIZE || x+j >= MAP_SIZE) { continue; } // out of bounds check

		auto& tile = tiles[y + i][x + j];
		if (tile.isEmpty) { continue; }

		if (CheckCollisionRecs(hitbox, tile.collisionRec)) {
			collisionTiles.push_back(tile);

			if (tile.isStaircase && tile.health <= 0) {
				foundStaircase = true;
				tile.isStaircase = false;
			}
		}
	}}
	return collisionTiles;
}
