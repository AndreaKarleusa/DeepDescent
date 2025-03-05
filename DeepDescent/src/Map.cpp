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
			tiles[i][j].Draw(textureSheet);
		}
	}
}

void Map::Generate()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{

			Vector2 tilePos = { (float)(j*TILE_SIZE), (float)(i*TILE_SIZE) };
			int spriteID = RandomInt(MAX_TILE_ID);
			
			tiles[i][j].Regenerate(tilePos, spriteID);
		}
	}
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

int Map::RandomInt(const int& maxInt)
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, maxInt); 

	return dist(gen);
}

Tile::Tile() {
	position = { 0.0f, 0.0f };
	spriteID = 0;
	isEmpty = true;
	isStaircase = false;
}

void Tile::Regenerate(Vector2 pos, int sID)
{
	position = pos;
	spriteID = sID;
	spriteRec = { (float)(spriteID*TILE_SIZE), 0, TILE_SIZE, TILE_SIZE };
	isEmpty = !(spriteID >= 2);
}

void Tile::Draw(Texture2D textureSheet)
{
	DrawTextureRec(textureSheet, spriteRec, position, WHITE);
}