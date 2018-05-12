#pragma once

#include "Graphics.h"

class Sprites {
public:
	static void DrawGameOver(int x, int y, Graphics& gfx);   // 350, 265 for screen center
	static void DrawTitle(int x, int y, Graphics& gfx);   // 290, 225 for screen center
};