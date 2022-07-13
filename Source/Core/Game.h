#pragma once
#include "Window.h"
#include "../Util/Timer.h"

class Game {
private:
	SPtr<Window> gWindow;
	//Starts up SDL and creates window
	bool init();
	//Frees media and shuts down SDL
	void close();
public:
	//Screen dimension constants
	// 3 : 4 proprtions
	static const int SCREEN_WIDTH = 896;
	static const int SCREEN_HEIGHT = 672;
	static const int SCREEN_FPS = 60;
	static const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
	Game() = default;
	Game(const Game&) = delete;
	Game(Game&) = delete;
	Game(Game&&) = delete;
	void run();

};