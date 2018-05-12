#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "SoundEffect.h"
#include "FrameTimer.h"
#include <random>
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
	static constexpr int nFood = 15;
	static constexpr int nPoison = 200;
	static constexpr int nObstacles = 15;
	static constexpr float snekMovePeriod = 0.3f;
	static constexpr float poisonSpawnPeriod = 10.0f;
	static constexpr bool sound = true;
	MainWindow& wnd;
	Graphics gfx;
	FrameTimer ft;
	std::mt19937 rng;
	Board brd;
	Snake snek;
	Vec2 deltaLoc;   // Snek Movement Vector
	Sound sndTitle = Sound(L"Sounds\\Title.wav");
	Sound sndMusic = Sound(L"Sounds\\Music_Loop.wav", 0.0f, 3.0f);
	SoundEffect sfxSlither = SoundEffect({ L"Sounds\\Slither0.wav", L"Sounds\\Slither1.wav", L"Sounds\\Slither2.wav" });
	SoundEffect sfxEat = SoundEffect({ L"Sounds\\Eat.wav" });
	SoundEffect sfxFart = SoundEffect({ L"Sounds\\Fart.wav" });
	bool gameStarted = false;
	bool gameOver = false;
	bool moveInhibit = false;   // Stops user from changing movement direction multiple times before snek actually moves
	float snekMoveCounter = 0.0f;   // Measures time for Snek Movement
	float poisonSpawnCounter = 0.0f;
};