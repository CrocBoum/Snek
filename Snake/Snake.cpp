#include "Snake.h"

#include <assert.h>


Snake::Snake(const Vec2& loc_in):
	headLoc(loc_in) {

	tail[0] = headLoc;
}

void Snake::Draw(Graphics& gfx, const Board& brd) const {
	for (int i = 0; i < length; i++) {
		Color c;
		if (i == 0) {
			c = headColor;
		}
		else {
			c = tailColors[(i - 1) % 4];
		}
		gfx.DrawRect(int(brd.GetPos().x) + int(tail[i].x) * brd.GetTileSize() + 1, int(brd.GetPos().y) + int(tail[i].y) * brd.GetTileSize() + 1, brd.GetTileSize() - 2, brd.GetTileSize() - 2, c);
	}
}

void Snake::MoveBy(const Vec2& deltaLoc) {
	for (int i = length - 1; i > 0; i--) {
		tail[i] = tail[i - 1];
	}
	tail[0] += deltaLoc;
}

void Snake::MoveAndGrowBy(const Vec2& deltaLoc, const int len) {
	assert(length < maxLength);

	tail[length] = tail[length - 1];
	MoveBy(deltaLoc);
	length++;
}