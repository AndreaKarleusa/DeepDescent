#include "Map.hpp"
#include "raylib.h"
#include <random>

Map::Map() { Generate(); }

void Map::LoadAssets() 
{
	spriteSheet = LoadImage("assets/Spritesheet512.png");
	textureSheet = LoadTextureFromImage(spriteSheet);
	UnloadImage(spriteSheet);
}
	
void Map::Draw()
{
	const int screenWidth = GetScreenWidth();
	const int screenHeight = GetScreenHeight();

	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			Rectangle frameRec = { (tileSprites[i][j] * TILE_SIZE, 0.0f, TILE_SIZE, TILE_SIZE};
			Vector2 position = { (j * TILE_SIZE) + (screenWidth / 2) - (MAP_SIZE * TILE_SIZE / 2),
								 (i * TILE_SIZE) + (screenHeight / 2) - (MAP_SIZE * TILE_SIZE / 2) };

			DrawTextureRec(textureSheet, frameRec, position, WHITE);
		}
	}
}

void Map::Generate()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			int tile = RandomInt(4); // maybe change the hard coded value to a static const variable

			// if the tile is walkable

			tileSprites[i][j] = tile;
			collisionBoxes[i][j] = (tile > 2);
		}
	}
}

int Map::RandomInt(const int& maxInt)
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, maxInt); 

	return dist(gen);
}