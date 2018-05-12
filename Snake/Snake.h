#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Board.h"


class Snake {
public:
	Snake(const Vec2& loc_in);
	void Draw(Graphics& gfx, const Board& brd) const;
	void MoveBy(const Vec2& deltaLoc);
	void MoveAndGrowBy(const Vec2& deltaLoc, const int len);
	void MoveAndShrinkBy(const Vec2& deltaLoc, const int len);
	Vec2 GetHeadLoc() const { return tail[0]; }
	Vec2 GetNextHeadLoc(const Vec2& deltaLoc) const;
	bool HeadIsOn(const Vec2& loc) const;
	bool IsOn(const Vec2& loc) const;
	bool IsOnWithoutEnd(const Vec2& loc) const;
	const int GetLength() const { return length; }
	const int GetMaxLength() const { return maxLength; }
private:
	static constexpr int maxLength = 100;
	Vec2 headLoc;
	Vec2 tail[maxLength - 1];
	Color headColor = Colors::Yellow;
	Color tailColors[4] = { {10, 100, 32}, {10, 130, 48}, {18, 160, 48}, {10, 130, 48} };
	int length = 1;
};