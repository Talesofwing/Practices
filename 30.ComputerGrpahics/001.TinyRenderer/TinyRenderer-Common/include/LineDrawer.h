#pragma once

#include "tgaimage.h"

class LineDrawer {
	LineDrawer() = delete;
	LineDrawer(const LineDrawer&) = delete;

	LineDrawer& operator=(const LineDrawer&) = delete;

public:
	static void DrawLine_Fast(int ax, int ay, int bx, int by, TGAImage& framebuffer, const TGAColor& color);
	static void DrawLine_Slow(int ax, int ay, int bx, int by, TGAImage& framebuffer, const TGAColor& color);

	static void DrawTriangle(
		int ax, int ay,
		int bx, int by,
		int cx, int cy,
		TGAImage& framebuffer, const TGAColor& color
	);
};

