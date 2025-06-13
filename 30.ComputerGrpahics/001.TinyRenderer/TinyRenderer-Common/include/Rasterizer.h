#pragma once

#include "tgaimage.h"

class Rasterizer {
	Rasterizer() = delete;
	Rasterizer(const Rasterizer&) = delete;

	Rasterizer& operator=(const Rasterizer&) = delete;

public:
	static void Triangle_Old(
		int ax, int ay,
		int bx, int by,
		int cx, int cy,
		TGAImage& framebuffer, const TGAColor& color
	);

	static void Triangle(
		int ax, int ay,
		int bx, int by,
		int cx, int cy,
		TGAImage& framebuffer, const TGAColor& color
	);

private:
	static std::tuple<int, int, int, int> CalcAABB(
		int ax, int ay,
		int bx, int by,
		int cx, int cy
	);

	static bool IsBackfaceCulling(
		int ax, int ay,
		int bx, int by,
		int cx, int cy
	);

	static bool IsInsideTriangle(
		int ax, int ay,
		int bx, int by,
		int cx, int cy,
		int px, int py
	);
};

