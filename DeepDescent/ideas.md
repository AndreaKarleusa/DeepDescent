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