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
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			Rectangle frameRec = { (float)(tileData[i][j] * TILE_SIZE), 0.0f, TILE_SIZE, TILE_SIZE};
			Vector2 position = { j * TILE_SIZE, i * TILE_SIZE };

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
			tileData[i][j] = RandomInt(4);
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