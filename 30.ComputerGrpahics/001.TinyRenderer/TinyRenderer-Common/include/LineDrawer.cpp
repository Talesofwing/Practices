
#include "LineDrawer.h"

void LineDrawer::DrawLine_Fast(const zer0::vec2& start, const zer0::vec2& end, TGAImage& framebuffer, const TGAColor& color) {
	int ax = start.x, ay = end.y;
	int bx = start.y, by = end.y;

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

void LineDrawer::DrawLine_Slow(const zer0::vec2& start, const zer0::vec2& end, TGAImage& framebuffer, const TGAColor& color) {
	int ax = start.x, ay = end.y;
	int bx = start.y, by = end.y;

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

void LineDrawer::DrawTriangle(const zer0::vec2& p1, const zer0::vec2& p2, const zer0::vec2& p3, TGAImage& framebuffer, const TGAColor& color)
{
	DrawLine_Fast(p1, p2, framebuffer, color);
	DrawLine_Fast(p3, p2, framebuffer, color);
	DrawLine_Fast(p3, p1, framebuffer, color);
	DrawLine_Fast(p1, p3, framebuffer, color);
}
