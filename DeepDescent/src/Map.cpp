#include "Map.hpp"
#include <raylib.h>
#include <random>
#include <iostream>

Map::Map() { }
Map::~Map() { UnloadTexture(spriteSheet); }

void Map::LoadAssets() 
{
	Image img = LoadImage("assets/tiles.png");
	spriteSheet = LoadTextureFromImage(img);
	UnloadImage(img);
}
	
void Map::Draw()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			tiles[i][j].Draw(spriteSheet);
		}
	}
}

void Map::Update()
{
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			tiles[i][j].Update();
		}
	}
}

// TODO: tweak the values as they should be
// NOTE: on the right path but make it better
void Map::Generate()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{

			Vector2 tilePos = { (float)(j*TILE_SIZE), (float)(i*TILE_SIZE) };
			float randomFloat = RandomFloat();

			int spriteID = 0; // = RandomInt(MAX_TILE_ID);

			if (randomFloat <= 0.65f)
				spriteID = 0;
			else if (randomFloat <= 0.7f)
				spriteID = 1;
			else if (randomFloat <= 0.8f)
				spriteID = 2;
			else if (randomFloat <= 0.9f)
				spriteID = 3;
			else 
				spriteID = 4;
			
			tiles[i][j].Generate(tilePos, spriteID);
		}
	}
	GenerateStaircase();
}

Vector2 Map::GetEmptyTile()
{
	int x = 0;
	int y = 0;

	while (!tiles[y][x].isEmpty) {
		x = RandomInt(MAP_SIZE - 1);
		y = RandomInt(MAP_SIZE - 1);
	}

	return tiles[y][x].position;
}
void Map::GenerateStaircase() 
{
	int x = RandomInt(MAP_SIZE - 1);
	int y = RandomInt(MAP_SIZE -1);

	while (tiles[y][x].isEmpty) {
		x = RandomInt(MAP_SIZE - 1);
		y = RandomInt(MAP_SIZE - 1);
	}

	tiles[y][x].isStaircase =  true;
	std::cout << x << " " << y << std::endl;
}
int Map::RandomInt(const int& maxInt)
{
	std::uniform_int_distribution<int> dist(0, maxInt); 
	return dist(gen);
}
float Map::RandomFloat() {
	std::uniform_real_distribution<float>  dist(0.0f, 1.0f);
	return dist(gen);
}




Tile::Tile() {}

void Tile::Generate(Vector2 pos, int sID)
{
	position = pos;

	spriteID = sID;
	defaultSpriteRec = { (float)(spriteID * TILE_SIZE), 0, TILE_SIZE, TILE_SIZE };
	spriteRec = defaultSpriteRec;

	isEmpty = (spriteID < 2); // the first 2 tiles are empty
	isStaircase = false;

	collisionRec = {
		position.x, position.y,
		TILE_SIZE, TILE_SIZE
	};
	
	health = MAX_HEALTH;
}

void Tile::Draw(Texture2D spriteSheet)
{
	DrawTextureRec(spriteSheet, spriteRec, position, WHITE);
}

// TODO: Just... clean this up... pls.
// IDEA: put the sprites in a sprite rect array
//		 the same way you have for tools
void Tile::Update()
{
	if (health != MAX_HEALTH) {
		// moves the sprite rec to the broken tile version
		spriteRec.x = 3*TILE_SIZE + defaultSpriteRec.x ;
	}
	if (health <= 0 && !isStaircase) {
		spriteRec.x = 0;
		isEmpty = true;
	}
	if (health <= 0 && isStaircase) {
		spriteRec.x = 8 * TILE_SIZE;
		isEmpty = false;
	}
}

void Tile::Damage(const float damage) 
{
	health -= damage;
}