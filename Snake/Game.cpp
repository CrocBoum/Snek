#include "Game.h"
#include "MainWindow.h"
#include "Sprites.h"


Game::Game(MainWindow& wnd) :
	wnd(wnd),
	gfx(wnd),
	ft(),
	rng(std::random_device()()),
	brd({ 50.0f, 50.0f }),
	snek({ 1.0f, 1.0f }),
	deltaLoc({ 1.0f, 0.0f }) {

	if (sound) {
		sndTitle.Play(1.0f, 1.0f);
	}

	brd.SpawnRandomContents(rng, Board::Content::Food, nFood, snek, deltaLoc);
	brd.SpawnRandomContents(rng, Board::Content::Poison, nPoison, snek, deltaLoc);
	brd.SpawnRandomContents(rng, Board::Content::Obstacle, nObstacles, snek, deltaLoc);
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
		poisonSpawnCounter += dt;

		if (!moveInhibit) {
			if (wnd.kbd.KeyIsPressed(VK_UP)) {
				const Vec2 newDeltaLoc = { 0.0f, -1.0f };
				if (deltaLoc != newDeltaLoc * -1) {
					deltaLoc = newDeltaLoc;
					moveInhibit = true;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
				const Vec2 newDeltaLoc = { 0.0f, 1.0f };
				if (deltaLoc != newDeltaLoc * -1) {
					deltaLoc = newDeltaLoc;
					moveInhibit = true;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
				const Vec2 newDeltaLoc = { -1.0f, 0.0f };
				if (deltaLoc != newDeltaLoc * -1) {
					deltaLoc = newDeltaLoc;
					moveInhibit = true;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
				const Vec2 newDeltaLoc = { 1.0f, 0.0f };
				if (deltaLoc != newDeltaLoc * -1) {
					deltaLoc = newDeltaLoc;
					moveInhibit = true;
				}
			}
		}


		if (poisonSpawnCounter >= poisonSpawnPeriod) {
			poisonSpawnCounter -= poisonSpawnPeriod;

			brd.SpawnRandomContents(rng, Board::Content::Poison, 1, snek, deltaLoc);
		}


		if (snekMoveCounter >= snekMovePeriod) {
			moveInhibit = false;
			snekMoveCounter -= snekMovePeriod;

			Vec2 nextLoc = snek.GetNextHeadLoc(deltaLoc);

			if (snek.IsOnWithoutEnd(nextLoc)) {
				gameOver = true;
				if (sound) {
					sfxFart.Play(rng, 1.2f);
					sndMusic.StopAll();
				}
			}

			if (brd.IsOutSide(nextLoc)) {
				gameOver = true;
				if (sound) {
					sfxFart.Play(rng, 1.2f);
					sndMusic.StopAll();
				}
			}

			switch (brd.GetContent(nextLoc)) {
			case Board::Content::Empty:
				snek.MoveBy(deltaLoc);
				if (sound) {
					sfxSlither.Play(rng, 0.1f);
				}
				break;
			case Board::Content::Food:
				snek.MoveAndGrowBy(deltaLoc, 1);
				brd.SpawnRandomContents(rng, Board::Content::Food, 1, snek, deltaLoc);
				brd.SpawnRandomContents(rng, Board::Content::Obstacle, 1, snek, deltaLoc);
				brd.RemoveContent(nextLoc);
				if (sound) {
					sfxEat.Play(rng, 1.0f);
				}
				break;
			case Board::Content::Poison:
				if (snek.GetLength() > 3) {
					brd.RemoveContent(nextLoc);
					snek.MoveAndShrinkBy(deltaLoc, 3);
					if (sound) {
						sfxFart.Play(rng, 0.6f);
					}
				}
				else {
					gameOver = true;
					if (sound) {
						sfxFart.Play(rng, 1.2f);
						sndMusic.StopAll();
					}
				}
				break;
			case Board::Content::Obstacle:
				gameOver = true;
				if (sound) {
					sfxFart.Play(rng, 1.2f);
					sndMusic.StopAll();
				}
				break;
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
	else if (gameOver) {
		Sprites::DrawGameOver(350, 265, gfx);
	}
	else {
		brd.Draw(gfx);
		snek.Draw(gfx, brd);
	}
}
