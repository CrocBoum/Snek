#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include <random>

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
	const Vec2 GetPos() const { return pos; }
	const int GetWidth() const { return width; }
	const int GetHeight() const { return height; }
	const int GetTileSize() const { return tileSize; }
	bool IsOutSide(const Vec2& loc);
	void SpawnContent(const Vec2& loc, Content contentType, class Snake& snek, const Vec2& deltaLoc);
	void SpawnRandomContents(std::mt19937 rng, Content contentType, int amount, class Snake& snek, const Vec2& deltaLoc);
	void RemoveContent(const Vec2& loc);
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
	Color borderColor = Colors::LightGray;
};