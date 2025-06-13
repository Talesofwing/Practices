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

	static void Triangle(
		int ax, int ay, int az,
		int bx, int by, int bz,
		int cx, int cy, int cz,
		TGAImage& framebuffer, TGAImage& depthbuffer,
		const TGAColor& color
	);

private:
	static std::tuple<int, int, int, int> CalcAABB(
		int ax, int ay,
		int bx, int by,
		int cx, int cy
	);

	static double CalcSignedArea(
		int ax, int ay,
		int bx, int by,
		int cx, int cy
	);

	static std::tuple<double, double, double> CalcBarycentricCoordinates(
		int ax, int ay,
		int bx, int by,
		int cx, int cy,
		int px, int py
	);

	/// <summary>
	/// Backface-culling & Area < 1 culling
	/// </summary>
	static bool IsCulling(
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

