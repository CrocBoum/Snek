#pragma once

#include "Vec2.h"
#include "Graphics.h"

class Board {
public:
	enum class Content {
		Empty,
		Obstacle,
		Food,
		Poison
	};
public:
	Board(const Vec2& pos_in);
	void Draw(Graphics& gfx) const;
	const Content GetContent(const Vec2& loc) const;
	void SpawnContent(const Vec2& loc, Content contentType);
private:
	static constexpr int width = 35;
	static constexpr int height = 25;
	static constexpr int nCells = width * height;
	static constexpr int tileSize = 20;
	static constexpr int borderSize = 5;
	Vec2 pos;
	Content contents[nCells] = { Content::Empty };
	Color obstacleColor = Colors::Gray;
	Color foodColor = Colors::Red;
	Color poisonColor = { 64, 8, 64 };
	Color borderColor = Colors::Blue;
};