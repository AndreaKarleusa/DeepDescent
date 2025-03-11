# Ideas

Collision manager that takes care of all the collision logic.
```cpp
	
	class CollisionManager
	{
	public:
		Rectangle playerRect;
		Tile tiles[MAP_SIZE][MAP_SIZE];
	public:
		void Update(playerRect, playerVel);
		
		void TileCollision();
		void EnemyCollision();
	private:
		std::vector<Tile> CollisionTiles();
	};
```

Better random tile algorithm

```cpp
float Random(){ return randomFloat(0.0f, 1.0f); }
enum sprites {...};

float chance = Random();
float emptyChance = 0.5f;
float fullChance  = 1.0f - emptyChance;

if (tileGen < emptyChance) { sprites[empty] }
else {tile.sprite = sprites[(int)(chance/fullchance * tilesize)]; }

```

Better tile state and sprite managing

```cpp
	
	Rectangle sprites[2] = {
		Rectangle whole,
		Rectangle damaged
	};

	enum class TileType {
		whole,
		damaged
	};

	TileType tileState = State::whole


	Draw(sprites[tileState], positon);

```

Utils file with random number functions and useful shit