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
	CalculateOffset();
}
	
void Map::Draw()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			Rectangle frameRec = { tileSprites[i][j] * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
			Vector2 position = { j*TILE_SIZE + offset.x, i*TILE_SIZE + offset.y };

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

// the "magic" -1 is for the array offset
/*




PLAYER DOESNT SPAWN ON EMPTY





*/
Vector2 Map::GetEmptyTile()
{
	int x = RandomInt(MAP_SIZE-1);   
	int y = RandomInt(MAP_SIZE-1);


	while (collisionBoxes[y][x])
	{
		x = RandomInt(MAP_SIZE-1);
		y = RandomInt(MAP_SIZE-1);
	}

	std::cout << "Player x,y: " << x << ", " << y << endl;

	return Vector2{ x*TILE_SIZE + offset.x, y*TILE_SIZE + offset.y};
}

void Map::CalculateOffset()
{
	const int screenWidth = GetScreenWidth();
	const int screenHeight = GetScreenHeight();

	// offset = (half of width/height) - (half of map size)
	offset = {
		(float)(screenWidth / 2) - (MAP_SIZE * TILE_SIZE / 2),
		(float)(screenHeight / 2) - (MAP_SIZE * TILE_SIZE / 2)
	};

}

int Map::RandomInt(const int& maxInt)
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, maxInt); 

	return dist(gen);
}