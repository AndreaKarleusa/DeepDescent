#pragma once
#include "raylib.h"
#include <deque>

// LAZY FLOOD FILL for ore veins
// min veins = 2, max veins = 5
// every generation it keeps track of the empty ones and puts them in a list
class Map
{
private:
	const int MAP_SIZE = 8;
	const int TILE_SIZE = 64;
	int tileData [8][8];

	// Textures
	Image spriteSheet;
	Texture2D textureSheet;
	
	// algo params
	float chance = 100.0f;
	float decay = 0.9985f;
	std::deque<int> tilesQueue;
	const int MIN_VEINS = 2;
	const int MAX_VEINS = 5;

public:
	Map();

	//REMEMBER: need to load textures AFTER InitWindow() function! else it just crashes for some reason
	void LoadAssets();
	void Draw();
	void Update();
	void Generate();

	bool DamageTile(const Vector2& tilePos, const int& dmg);
	Vector2 GetEmptyTile();

private:
	int RandomInt(const int& maxInt);
};