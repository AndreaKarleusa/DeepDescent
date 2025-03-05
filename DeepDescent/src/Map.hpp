#pragma once
#include "raylib.h"
#include "Settings.hpp"

//It's simpler just to pick a random distribution
//that favours lower numbers in a range (log distribution)
class Map
{
public:
	
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
	int RandomInt(const int& maxInt);
	
	Vector2 GetEmptyTile();
	
	bool DamageTile(const Vector2& tilePos, const int& dmg);
};

