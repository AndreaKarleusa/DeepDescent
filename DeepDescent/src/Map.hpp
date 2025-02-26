#pragma once
#include "raylib.h"
#include <deque>

// LAZY FLOOD FILL for ore veins
// min veins = 2, max veins = 5
// every generation it keeps track of the empty ones and puts them in a list

//It's simpler just to pick a random distribution
//that favours lower numbers in a range (log distribution)
class Map
{
private:
	static const int MAP_SIZE = 8;
	static const int TILE_SIZE = 64;
	
	int tileSprites [MAP_SIZE][MAP_SIZE];
	bool collisionBoxes [MAP_SIZE][MAP_SIZE];

	Image spriteSheet;
	Texture2D textureSheet;

public:
	Map();

	//REMEMBER: need to load textures AFTER InitWindow() function! else it just crashes for some reason
	void LoadAssets();
	void Draw();
	void Update(); // listen for player hits and other events
	void Generate();

	bool DamageTile(const Vector2& tilePos, const int& dmg);

private:
	int RandomInt(const int& maxInt);
};