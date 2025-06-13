
#include "LineDrawer.h"

void LineDrawer::DrawLine_Fast(
	int ax, int ay,
	int bx, int by,
	TGAImage& framebuffer, const TGAColor& color)
{
	bool steep = std::abs(ax - bx) < std::abs(ay - by);
	if (steep) {
		std::swap(ax, ay);
		std::swap(bx, by);
	}

	if (ax > bx) {
		std::swap(ax, bx);
		std::swap(ay, by);
	}

	int y = ay;
	int ierror = 0;
	for (int x = ax; x <= bx; ++x) {
		if (steep) {
			framebuffer.set(y, x, color);
		} else {
			framebuffer.set(x, y, color);
		}

		ierror += 2 * std::abs(by - ay);
		y += (by > ay ? 1 : -1) * (ierror > bx - ax);
		ierror -= (2 * (bx - ax)) * (ierror > bx - ax);
	}
}

void LineDrawer::DrawLine_Slow(
	int ax, int ay,
	int bx, int by,
	TGAImage& framebuffer, const TGAColor& color)
{
	bool steep = std::abs(ax - bx) < std::abs(ay - by);
	if (steep) {
		std::swap(ax, ay);
		std::swap(bx, by);
	}

	if (ax > bx) {
		std::swap(ax, bx);
		std::swap(ay, by);
	}

	int y = ay;
	int ierror = 0;
	for (int x = ax; x <= bx; ++x) {
		if (steep) {
			framebuffer.set(y, x, color);
		} else {
			framebuffer.set(x, y, color);
		}

		ierror += 2 * std::abs(by - ay);
		if (ierror > bx - ax) {
			y += by > ay ? 1 : -1;
			ierror -= 2 * (bx - ax);
		}
	}
}

void LineDrawer::DrawTriangle(
	int ax, int ay,
	int bx, int by,
	int cx, int cy,
	TGAImage& framebuffer, const TGAColor& color)
{

	DrawLine_Fast(ax, ay, bx, by, framebuffer, color);
	DrawLine_Fast(cx, cy, bx, by, framebuffer, color);
	DrawLine_Fast(cx, cy, ax, ay, framebuffer, color);
	DrawLine_Fast(ax, ay, cx, cy, framebuffer, color);
}
