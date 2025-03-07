#include "Player.hpp"
#include "Map.hpp"

#include <vector>
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

void Player::Update(Tile tiles[MAP_SIZE][MAP_SIZE], const Camera2D& cam)
{
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

	// TODO: calculate the player-mouse distance
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), cam);
		int x = mousePosition.x / TILE_SIZE;
		int y = mousePosition.y / TILE_SIZE;

		if (!tiles[y][x].isEmpty) { tiles[y][x].Damage(blockDamage); };
	}
}

void Player::Spawn(const Vector2& spawnPos)
{
	position = spawnPos;
}

// OPTIMIZATION:
// + instead of the whole array of tiles give the function only tiles around the player
// + use iterators to clean up the code
std::vector<Tile> Player::CheckCollision(Tile tiles[MAP_SIZE][MAP_SIZE])
{
	std::vector<Tile> collisionTiles;
	Rectangle hitbox = { position.x, position.y, (float)playerSprite.width, (float)playerSprite.height };

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (!(tiles[i][j].isEmpty) && CheckCollisionRecs(hitbox, tiles[i][j].collisionRec)) {
				collisionTiles.push_back(tiles[i][j]);

				if (tiles[i][j].isStaircase && tiles[i][j].health <= 0) {
					foundStaircase = true; 
					tiles[i][j].isStaircase = false;
				}
			}
		}
	}
	return collisionTiles;
}
