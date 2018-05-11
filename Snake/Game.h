#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "Board.h"
#include "Snake.h"


class Game {
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(const float dt);
private:
	static constexpr int tileSize = 10;
	static constexpr float snekMovePeriod = 0.3f;
	MainWindow& wnd;
	Graphics gfx;
	FrameTimer ft;
	Board brd;
	Snake snek;
	Vec2 deltaLoc;   // Snek Movement Vector
	float snekMoveCounter = 0.0f;
};