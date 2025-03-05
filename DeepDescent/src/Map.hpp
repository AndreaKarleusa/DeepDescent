#pragma once
#include "raylib.h"
#include "Settings.hpp"

class Tile {
public:
	int spriteID;
	Rectangle spriteRec;
	Vector2 position;

	const int MAX_HEALTH = 15;
	int health = MAX_HEALTH;

	bool isEmpty;
	bool isStaircase;
public:
	Tile();

	void Regenerate(Vector2 pos, int sID);
	void Draw(Texture2D textureSheet);
	void Update();
	void Damage(const int damage);
};

//It's simpler just to pick a random distribution
//that favours lower numbers in a range (log distribution)
class Map
{
public:
	Image spriteSheet;
	Texture2D textureSheet;
	Tile tiles[MAP_SIZE][MAP_SIZE];

	const int MAX_TILE_ID = 4;

public:
	Map();

	//REMEMBER: need to load textures AFTER InitWindow() function! else it just crashes for some reason
	void LoadAssets();
	void Draw();
	void Update(); // listen for player hits and other events
	
	void Generate();
	int RandomInt(const int& maxInt);
	
	Vector2 GetEmptyTile();
	
	bool DamageTile(const Vector2& tilePos, const int& dmg);
};
