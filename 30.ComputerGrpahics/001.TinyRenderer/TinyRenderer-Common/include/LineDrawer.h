#pragma once

#include "tgaimage.h"
#include "zer0Math.h"

class LineDrawer {
	LineDrawer() = delete;
	LineDrawer(const LineDrawer&) = delete;

	LineDrawer& operator=(const LineDrawer&) = delete;

public:
	static void DrawLine_Fast(const zer0::vec2& start, const zer0::vec2& end, TGAImage& framebuffer, const TGAColor& color);
	static void DrawLine_Slow(const zer0::vec2& start, const zer0::vec2& end, TGAImage& framebuffer, const TGAColor& color);

	static void DrawTriangle(const zer0::vec2& p1, const zer0::vec2& p2, const zer0::vec2& p3, TGAImage& framebuffer, const TGAColor& color);
};

