#pragma once
#include "raylib.h"
#include "Settings.hpp"

// LAZY FLOOD FILL for ore veins
// min veins = 2, max veins = 5
// every generation it keeps track of the empty ones and puts them in a list

//It's simpler just to pick a random distribution
//that favours lower numbers in a range (log distribution)
class Map
{
public:
	
	int tileSprites [MAP_SIZE][MAP_SIZE];
	bool collisionBoxes [MAP_SIZE][MAP_SIZE];

	Image spriteSheet;
	Texture2D textureSheet;
	Vector2 offset = { 0,0 };

public:
	Map();

	//REMEMBER: need to load textures AFTER InitWindow() function! else it just crashes for some reason
	void LoadAssets();
	void Draw();
	void Update(); // listen for player hits and other events
	
	void Generate();
	void CalculateOffset();
	int RandomInt(const int& maxInt);
	
	Vector2 GetEmptyTile();
	Vector2 ToGlobalCords(int x, int y);
	
	bool DamageTile(const Vector2& tilePos, const int& dmg);
};