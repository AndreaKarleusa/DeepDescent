#pragma once
#include "raylib.h"
#include "Settings.hpp"
#include <random>


class Tile {
public:
	Rectangle defaultSpriteRec;
	Rectangle spriteRec;
	Rectangle collisionRec;
	Vector2 position;

	// TODO:
	// remove the is- prefix
	int spriteID = 0;
	bool isEmpty = true;
	bool isStaircase = false;

	const float MAX_HEALTH = 2.0f;
	float health = MAX_HEALTH;

public:
	Tile();

	void Generate(Vector2 pos, int sID);
	void Draw(Texture2D spriteSheet);
	void Update();
	void Damage(const float damage);
};

//It's simpler just to pick a random distribution
//that favours lower numbers in a range (log distribution)
class Map
{
public:
	Texture2D spriteSheet;
	Tile tiles[MAP_SIZE][MAP_SIZE];

	const int MAX_TILE_ID = 4; 

	std::random_device rd;
	std::mt19937 gen = std::mt19937(rd());

public:
	Map();
	~Map();

	//REMEMBER: need to load textures AFTER InitWindow() function! else it just crashes for some reason
	void LoadAssets();
	void Draw();
	void Update(); // listen for player hits and other events
	
	void Generate();
	void GenerateStaircase();

	int RandomInt(const int& maxInt);
	float RandomFloat();

	Vector2 GetEmptyTile();

	
	bool DamageTile(const Vector2& tilePos, const int& dmg);
};
