#include "Game.h"
#include "MainWindow.h"
#include "Sprites.h"


Game::Game(MainWindow& wnd) :
	wnd(wnd),
	gfx(wnd),
	ft(),
	rng(std::random_device()()),
	brd({50.0f, 50.0f}),
	snek({ 1.0f, 1.0f }),
	deltaLoc({ 1.0f, 0.0f }) {

	if (sound) {
		sndTitle.Play(1.0f, 1.0f);
	}
}

void Game::Go() {
	gfx.BeginFrame();
	const float dt = ft.Mark();
	UpdateModel(dt);
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(const float dt) {
	if (gameStarted && !gameOver) {
		snekMoveCounter += dt;

		if (wnd.kbd.KeyIsPressed(VK_UP)) {
			deltaLoc = { 0.0f, -1.0f };
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
			deltaLoc = { 0.0f, 1.0f };
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
			deltaLoc = { -1.0f, 0.0f };
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
			deltaLoc = { 1.0f, 0.0f };
		}


		if (snekMoveCounter >= snekMovePeriod) {
			snekMoveCounter -= snekMovePeriod;

			if (wnd.kbd.KeyIsPressed(VK_SHIFT)) {
				snek.MoveAndGrowBy(deltaLoc, 1);
			}
			else {
				snek.MoveBy(deltaLoc);
			}
			if (sound) {
				sfxSlither.Play(rng, 0.1f);
			}
		}
	}
	else if (!gameStarted) {
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			gameStarted = true;
			if (sound) {
				sndMusic.Play(1.0f, 0.1f);
			}
		}
	}
}

void Game::ComposeFrame() {

	if (!gameStarted) {
		Sprites::DrawTitle(290, 225, gfx);
	}
	else {
		brd.Draw(gfx);
		snek.Draw(gfx, brd);
	}
}
