#include "Map.hpp"
#include "raylib.h"
#include <random>
#include <iostream>
using namespace std;

Map::Map() { }

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
			Rectangle frameRec = { tileSprites[i][j] * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
			Vector2 position = { j*TILE_SIZE, i*TILE_SIZE };

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

			tileSprites[i][j] = tile;
			collisionBoxes[i][j] = (tile > 2);
		}
	}
}


Vector2 Map::GetEmptyTile()
{
	int x, y = 0;

	do{
		x = RandomInt(MAP_SIZE-1);
		y = RandomInt(MAP_SIZE-1);

	} while (collisionBoxes[y][x]);

	return Vector2{ (float)(x*TILE_SIZE), (float)(y*TILE_SIZE) };
}

int Map::RandomInt(const int& maxInt)
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, maxInt); 

	return dist(gen);
}