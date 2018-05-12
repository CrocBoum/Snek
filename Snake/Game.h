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
	static constexpr int tileSize = 10;
	static constexpr float snekMovePeriod = 0.3f;
	static constexpr bool sound = false;
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
	float snekMoveCounter = 0.0f;   // Measures time for Snek Movement
};