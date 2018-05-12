#include "Board.h"

#include <assert.h>
#include "Snake.h"


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

bool Board::IsOutSide(const Vec2& loc) {
	return loc.x < 0 || loc.x >= width || loc.y < 0 || loc.y >= height;
}

void Board::SpawnContent(const Vec2& loc, Content contentType, Snake& snek, const Vec2& deltaLoc) {
	assert(contents[int(loc.y) * width + int(loc.x)] == Content::Empty);
	assert(contentType != Content::Empty);
	assert(!snek.IsOn(loc));
	assert(snek.GetNextHeadLoc(deltaLoc) != loc);

	contents[int(loc.y) * width + int(loc.x)] = contentType;
}

void Board::SpawnRandomContents(std::mt19937 rng, Content contentType, int amount, Snake& snek, const Vec2& deltaLoc) {
	std::uniform_int_distribution<int> xDist = std::uniform_int_distribution<int>(0, width - 1);
	std::uniform_int_distribution<int> yDist = std::uniform_int_distribution<int>(0, height - 1);

	for (int i = 0; i < amount; i++) {
		bool valid = false;
		Vec2 newLoc;
		do {
			newLoc = { float(xDist(rng)), float(yDist(rng)) };
			if (contents[int(newLoc.y) * width + int(newLoc.x)] == Content::Empty && snek.GetNextHeadLoc(deltaLoc) != newLoc && !snek.IsOn(newLoc)) {
				valid = true;
			}
		} while (!valid);

		SpawnContent(newLoc, contentType, snek, deltaLoc);
	}
}

void Board::RemoveContent(const Vec2& loc) {
	assert(contents[int(loc.y) * width + int(loc.x)] != Content::Empty);

	contents[int(loc.y) * width + int(loc.x)] = Content::Empty;
}