#include "Game.h"
#include "MainWindow.h"


Game::Game(MainWindow& wnd) :
	wnd(wnd),
	gfx(wnd),
	ft() {

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

}
