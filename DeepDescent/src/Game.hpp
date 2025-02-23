#pragma once

class Game
{
private:
	const char* SCREEN_TITLE = "Deep Descent";
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 720;
	const int FPS = 60;
public:
	Game();
	~Game();
public:
	void Run();
	void Draw();
	void Update();

};