#include "Rasterizer.h"
#include "iostream"

//
// There may be some redundant calculations, such as computing the area.
// The main purpose is to make it clearer how each step is derived.
//

void Rasterizer::Triangle_Old(
	int ax, int ay,
	int bx, int by,
	int cx, int cy,
	TGAImage& framebuffer, const TGAColor& color)
{
	// Check backface-culling
	if (IsCulling(ax, ay, bx, by, cx, cy)) return;

	// Sort the vertices, a,b,c in ascending y order
	if (ay > by) { std::swap(ax, bx); std::swap(ay, by); }
	if (ay > cy) { std::swap(ax, cx); std::swap(ay, cy); }
	if (by > cy) { std::swap(bx, cx); std::swap(by, cy); }

	int total_height = cy - ay;

	if (ay != by) {
		int segment_height = by - ay;
		for (int y = ay; y <= by; ++y) {
			int x1 = ax + (y - ay) * (cx - ax) / total_height;
			int x2 = ax + (y - ay) * (bx - ax) / segment_height;
			for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x) {
				framebuffer.set(x, y, color);
			}
		}
	}

	if (by != cy) {
		int segment_height = cy - by;
		for (int y = by; y <= cy; ++y) {
			int x1 = ax + (y - ay) * (cx - ax) / total_height;
			int x2 = bx + (y - by) * (cx - bx) / segment_height;
			for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x) {
				framebuffer.set(x, y, color);
			}
		}
	}
}

void Rasterizer::Triangle(
	int ax, int ay,
	int bx, int by,
	int cx, int cy,
	TGAImage& framebuffer, const TGAColor& color)
{
	if (IsCulling(ax, ay, bx, by, cx, cy)) return;

	int xmin, ymin, xmax, ymax;
	std::tie(xmin, ymin, xmax, ymax) = CalcAABB(ax, ay, bx, by, cx, cy);

	for (int x = xmin; x <= xmax; ++x) {
		for (int y = ymin; y <= ymax; ++y) {
			if (IsInsideTriangle(ax, ay, bx, by, cx, cy, x, y)) {
				framebuffer.set(x, y, color);
			}
		}
	}
}

void Rasterizer::Triangle(
	int ax, int ay, int az,
	int bx, int by, int bz,
	int cx, int cy, int cz,
	TGAImage& framebuffer, TGAImage& depthbuffer,
	const TGAColor& color)
{
	if (IsCulling(ax, ay, bx, by, cx, cy)) return;

	int xmin, ymin, xmax, ymax;
	std::tie(xmin, ymin, xmax, ymax) = CalcAABB(ax, ay, bx, by, cx, cy);

	for (int x = xmin; x <= xmax; ++x) {
		for (int y = ymin; y <= ymax; ++y) {
			double alpha, beta, gamma;
			std::tie(alpha, beta, gamma) = CalcBarycentricCoordinates(ax, ay, bx, by, cx, cy, x, y);
			if (alpha >= 0 && beta >= 0 && gamma >= 0) {
				unsigned char z = static_cast<unsigned char> (alpha * az + beta * bz + gamma * cz);
				if (z > depthbuffer.get(x, y)[0]) {
					depthbuffer.set(x, y, {z});
					framebuffer.set(x, y, color);
				}
			}
		}
	}
}

std::tuple<int, int, int, int> Rasterizer::CalcAABB(
	int ax, int ay,
	int bx, int by,
	int cx, int cy)
{
	int xmin, xmax, ymin, ymax;
	xmin = std::min(std::min(ax, bx), cx);
	xmax = std::max(std::max(ax, bx), cx);
	ymin = std::min(std::min(ay, by), cy);
	ymax = std::max(std::max(ay, by), cy);
	return std::tuple<int, int, int, int>(xmin, ymin, xmax, ymax);
}

double Rasterizer::CalcSignedArea(
	int ax, int ay,
	int bx, int by,
	int cx, int cy)
{
	return .5 * ((bx - ax) * (cy - ay) - (by - ay) * (cx - ax));
}

std::tuple<double, double, double> Rasterizer::CalcBarycentricCoordinates(
	int ax, int ay,
	int bx, int by,
	int cx, int cy,
	int px, int py)
{
	double total_area = CalcSignedArea(ax, ay, bx, by, cx, cy);
	double alpha = CalcSignedArea(px, py, bx, by, cx, cy) / total_area;
	double beta = CalcSignedArea(ax, ay, px, py, cx, cy) / total_area;
	double gamma = 1 - alpha - beta;
	return std::make_tuple(alpha, beta, gamma);
}

bool Rasterizer::IsCulling(
	int ax, int ay,
	int bx, int by,
	int cx, int cy)
{
	return CalcSignedArea(ax, ay, bx, by, cx, cy) <= 1;
}

bool Rasterizer::IsInsideTriangle(
	int ax, int ay,
	int bx, int by,
	int cx, int cy,
	int px, int py)
{
	// Using cross-product to test point inclusion in a triangle

	int ab_x = bx - ax, ab_y = by - ay;
	int bc_x = cx - bx, bc_y = cy - by;
	int ca_x = ax - cx, ca_y = ay - cy;
	int ap_x = px - ax, ap_y = py - ay;
	int bp_x = px - bx, bp_y = py - by;
	int cp_x = px - cx, cp_y = py - cy;

	int sign1 = ab_x * ap_y - ab_y * ap_x;
	int sign2 = bc_x * bp_y - bc_y * bp_x;
	int sign3 = ca_x * cp_y - ca_y * cp_x;

	return (sign1 > 0 && sign2 > 0 && sign3 > 0) || (sign1 < 0 && sign2 < 0 && sign3 < 0);
}
