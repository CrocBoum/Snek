#include "Board.h"

#include <assert.h>


Board::Board(const Vec2& pos_in):
	pos(pos_in) {

}

void Board::Draw(Graphics& gfx) const {
	assert(pos.x - borderSize >= 0);
	assert(pos.x + width + borderSize < Graphics::ScreenWidth);
	assert(pos.y - borderSize >= 0);
	assert(pos.y + height + borderSize < Graphics::ScreenHeight);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			switch (contents[y * width + x]) {
			case Content::Obstacle:
				gfx.DrawRect(int(pos.x) + x * tileSize + 1, int(pos.y) + y * tileSize + 1, tileSize - 2, tileSize - 2, obstacleColor);
				break;
			case Content::Food:
				gfx.DrawRect(int(pos.x) + x * tileSize + 1, int(pos.y) + y * tileSize + 1, tileSize - 2, tileSize - 2, foodColor);
				break;
			case Content::Poison:
				gfx.DrawRect(int(pos.x) + x * tileSize + 1, int(pos.y) + y * tileSize + 1, tileSize - 2, tileSize - 2, poisonColor);
				break;
			}
		}
	}

	// Border
	gfx.DrawRectByCorners(int(pos.x) - borderSize,       int(pos.y) - borderSize,        int(pos.x) + width * tileSize + borderSize - 1, int(pos.y) - 1,                                  borderColor);
	gfx.DrawRectByCorners(int(pos.x) - borderSize,       int(pos.y) + height * tileSize, int(pos.x) + width * tileSize + borderSize - 1, int(pos.y) + height * tileSize + borderSize - 1, borderColor);
	gfx.DrawRectByCorners(int(pos.x) - borderSize,       int(pos.y),                     int(pos.x) - 1,                                 int(pos.y) + height * tileSize - 1,              borderColor);
	gfx.DrawRectByCorners(int(pos.x) + width * tileSize, int(pos.y),                     int(pos.x) + width * tileSize + borderSize - 1, int(pos.y) + height * tileSize - 1,              borderColor);
}

const Board::Content Board::GetContent(const Vec2& loc) const {
	return contents[int(loc.y) * width + int(loc.x)];
}

void Board::SpawnContent(const Vec2& loc, Content contentType) {
	assert(contents[int(loc.y) * width + int(loc.x)] == Content::Empty);
	assert(contentType != Content::Empty);

	contents[int(loc.y) * width + int(loc.x)] = contentType;
}