#include "Map.hpp"
#include "raylib.h"
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

void Map::Generate()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{

			Vector2 tilePos = { (float)(j*TILE_SIZE), (float)(i*TILE_SIZE) };
			int spriteID = RandomInt(MAX_TILE_ID);
			
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

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, maxInt); 

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
}

void Tile::Draw(Texture2D spriteSheet)
{
	DrawTextureRec(spriteSheet, spriteRec, position, WHITE);
}

void Tile::Update()
{
	if (health != MAX_HEALTH) {
		spriteRec.x = 3*TILE_SIZE + defaultSpriteRec.x ; // moves the sprite rec to the broken tile version
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

void Tile::Damage(const int damage) 
{
	health -= damage;
}