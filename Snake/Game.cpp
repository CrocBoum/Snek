#include "Game.h"
#include "MainWindow.h"


Game::Game(MainWindow& wnd) :
	wnd(wnd),
	gfx(wnd),
	ft(),
	brd({50.0f, 50.0f}) {

}

void Game::Go() {
	gfx.BeginFrame();
	const float dt = ft.Mark();
	UpdateModel(dt);
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(const float dt) {

}

void Game::ComposeFrame() {
	brd.Draw(gfx);
}
