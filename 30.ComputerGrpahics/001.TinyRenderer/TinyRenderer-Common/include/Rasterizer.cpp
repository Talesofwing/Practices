#include "Rasterizer.h"

//
// There mp1.y be some redundant calculations, such as computing the area.
// The main purpose is to make it clearer how each step is derived.
//

void Rasterizer::Line_Without_If(vec2 start, vec2 end, TGAImage& framebuffer, const TGAColor& color) {
	bool steep = std::abs(start.x - end.x) < std::abs(start.y - end.y);
	if (steep) {
		std::swap(start.x, start.y);
		std::swap(end.x, end.y);
	}

	if (start.x > end.x) {
		std::swap(start.x, end.x);
		std::swap(start.y, end.y);
	}

	int y = static_cast<int>(start.y);
	int ierror = 0;
	for (int x = static_cast<int>(start.x); x <= end.x; ++x) {
		if (steep) {
			framebuffer.set(y, x, color);
		} else {
			framebuffer.set(x, y, color);
		}

		ierror += 2 * static_cast<int>(std::abs(end.y - start.y));
		y += (end.y > start.y ? 1 : -1) * (ierror > end.x - start.x);
		ierror -= (2 * static_cast<int>((end.x - start.x))) * (ierror > end.x - start.x);
	}
}

void Rasterizer::Line_With_If(vec2 start, vec2 end, TGAImage& framebuffer, const TGAColor& color) {
	bool steep = std::abs(start.x - end.x) < std::abs(start.y - end.y);
	if (steep) {
		std::swap(start.x, start.y);
		std::swap(end.x, end.y);
	}

	if (start.x > end.x) {
		std::swap(start.x, end.x);
		std::swap(start.y, end.y);
	}

	int y = static_cast<int>(start.y);
	int ierror = 0;
	for (int x = static_cast<int>(start.x); x <= end.x; ++x) {
		if (steep) {
			framebuffer.set(y, x, color);
		} else {
			framebuffer.set(x, y, color);
		}

		ierror += 2 * static_cast<int>(std::abs(end.y - start.y));
		if (ierror > end.x - start.x) {
			y += end.y > start.y ? 1 : -1;
			ierror -= 2 * static_cast<int>((end.x - start.x));
		}
	}
}

void Rasterizer::Triangle_Old(vec2 p1, vec2 p2, vec2 p3, TGAImage& framebuffer, const TGAColor& color)
{
	if (Wireframe) {
		Line_With_If(p1, p2, framebuffer, color);
		Line_With_If(p1, p3, framebuffer, color);
		Line_With_If(p2, p3, framebuffer, color);
	} else {
		// Check backface-culling
		if (Culling && IsCulling(p1, p2, p3)) return;

		// Sort the vertices, a,b,c in ascending y order
		if (p1.y > p2.y) { std::swap(p1.x, p2.x); std::swap(p1.y, p2.y); }
		if (p1.y > p3.y) { std::swap(p1.x, p3.x); std::swap(p1.y, p3.y); }
		if (p2.y > p3.y) { std::swap(p2.x, p3.x); std::swap(p2.y, p3.y); }

		int total_height = static_cast<int>(p3.y - p1.y);

		if (p1.y != p2.y) {
			int segment_height = static_cast<int>(p2.y - p1.y);
			for (int y = static_cast<int>(p1.y); y <= p2.y; ++y) {
				int x1 = static_cast<int>(p1.x + (y - p1.y) * (p3.x - p1.x) / total_height);
				int x2 = static_cast<int>((p1.x + (y - p1.y) * (p2.x - p1.x) / segment_height));
				for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x) {
					framebuffer.set(x, y, color);
				}
			}
		}

		if (p2.y != p3.y) {
			int segment_height = static_cast<int>(p3.y - p2.y);
			for (int y = static_cast<int>(p2.y); y <= p3.y; ++y) {
				int x1 = static_cast<int>(p1.x + (y - p1.y) * (p3.x - p1.x) / total_height);
				int x2 = static_cast<int>(p2.x + (y - p2.y) * (p3.x - p2.x) / segment_height);
				for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x) {
					framebuffer.set(x, y, color);
				}
			}
		}
	}
}

void Rasterizer::Triangle(const vec2& p1, const vec2& p2, const vec2& p3, TGAImage& framebuffer, const TGAColor& color) {
	if (Wireframe) {
		Line_With_If(p1, p2, framebuffer, color);
		Line_With_If(p1, p3, framebuffer, color);
		Line_With_If(p2, p3, framebuffer, color);
	} else {
		if (Culling && IsCulling(p1, p2, p3)) return;

		int xmin, ymin, xmax, ymax;
		std::tie(xmin, ymin, xmax, ymax) = CalcAABB(p1, p2, p3);

		for (int x = xmin; x <= xmax; ++x) {
			for (int y = ymin; y <= ymax; ++y) {
				if (IsInsideTriangle(p1, p2, p3, vec2(x, y))) {
					framebuffer.set(x, y, color);
				}
			}
		}
	}
}

void Rasterizer::Triangle(const vec3& p1, const vec3& p2, const vec3& p3, TGAImage& framebuffer, TGAImage& depthbuffer, const TGAColor& color) {
	if (Wireframe) {
		Line_With_If(p1, p2, framebuffer, color);
		Line_With_If(p1, p3, framebuffer, color);
		Line_With_If(p2, p3, framebuffer, color);
	} else {
		if (Culling && IsCulling(p1, p2, p3)) return;

		int xmin, ymin, xmax, ymax;
		std::tie(xmin, ymin, xmax, ymax) = CalcAABB(p1, p2, p3);

		for (int x = xmin; x <= xmax; ++x) {
			for (int y = ymin; y <= ymax; ++y) {
				double alpha, beta, gamma;
				std::tie(alpha, beta, gamma) = CalcBarycentricCoordinates(p1, p2, p3, vec2(x, y));
				if (alpha >= 0 && beta >= 0 && gamma >= 0) {
					unsigned char z = static_cast<unsigned char> (alpha * p1.z + beta * p2.z + gamma * p3.z);
					if (z > depthbuffer.get(x, y)[0]) {
						depthbuffer.set(x, y, {z});
						framebuffer.set(x, y, color);
					}
				}
			}
		}
	}
}

void Rasterizer::Triangle(
	const vec3& p1, const vec3& p2, const vec3& p3,
	const vec2& uv1, const vec2& uv2, const vec2& uv3,
	TGAImage& framebuffer, TGAImage& depthbuffer,
	const TGAImage& texturebuffer)
{
	if (Wireframe) {
		Line_With_If(p1, p2, framebuffer, texturebuffer.get(static_cast<const int>(uv1.x), static_cast<const int>(uv1.y)));
		Line_With_If(p1, p3, framebuffer, texturebuffer.get(static_cast<const int>(uv2.x), static_cast<const int>(uv2.y)));
		Line_With_If(p2, p3, framebuffer, texturebuffer.get(static_cast<const int>(uv3.x), static_cast<const int>(uv3.y)));
	} else {
		if (Culling && IsCulling(p1, p2, p3)) return;

		int xmin, ymin, xmax, ymax;
		std::tie(xmin, ymin, xmax, ymax) = CalcAABB(p1, p2, p3);

		for (int x = xmin; x <= xmax; ++x) {
			for (int y = ymin; y <= ymax; ++y) {
				double alpha, beta, gamma;
				std::tie(alpha, beta, gamma) = CalcBarycentricCoordinates(p1, p2, p3, vec2(x, y));
				if (alpha >= 0 && beta >= 0 && gamma >= 0) {
					unsigned char z = static_cast<unsigned char> (alpha * p1.z + beta * p2.z + gamma * p3.z);
					int u = std::clamp(static_cast<int>((alpha * uv1.x + beta * uv2.x + gamma * uv3.x) * texturebuffer.width()), 0, texturebuffer.width() - 1);
					int v = std::clamp(static_cast<int>((alpha * uv1.y + beta * uv2.y + gamma * uv3.y) * texturebuffer.height()), 0, texturebuffer.height() - 1);
					if (z > depthbuffer.get(x, y)[0]) {
						depthbuffer.set(x, y, {z});
						framebuffer.set(x, y, texturebuffer.get(u, v));
					}
				}
			}
		}
	}
}

void Rasterizer::Triangle(
	const vec3& p1, const vec3& p2, const vec3& p3,
	const vec2& uv1, const vec2& uv2, const vec2& uv3,
	const vec3& n1, const vec3& n2, const vec3& n3,
	TGAImage& framebuffer, TGAImage& depthbuffer,
	const TGAImage& texturebuffer)
{
	if (Wireframe) {
		Line_With_If(p1, p2, framebuffer, texturebuffer.get(static_cast<const int>(uv1.x), static_cast<const int>(uv1.y)));
		Line_With_If(p1, p3, framebuffer, texturebuffer.get(static_cast<const int>(uv2.x), static_cast<const int>(uv2.y)));
		Line_With_If(p2, p3, framebuffer, texturebuffer.get(static_cast<const int>(uv3.x), static_cast<const int>(uv3.y)));
	} else {
		if (Culling && IsCulling(p1, p2, p3)) return;

		int xmin, ymin, xmax, ymax;
		std::tie(xmin, ymin, xmax, ymax) = CalcAABB(p1, p2, p3);

		for (int x = xmin; x <= xmax; ++x) {
			for (int y = ymin; y <= ymax; ++y) {
				double alpha, beta, gamma;
				std::tie(alpha, beta, gamma) = CalcBarycentricCoordinates(p1, p2, p3, vec2(x, y));
				if (alpha >= 0 && beta >= 0 && gamma >= 0) {
					unsigned char z = static_cast<unsigned char> (alpha * p1.z + beta * p2.z + gamma * p3.z);
					int u = std::clamp(static_cast<int>((alpha * uv1.x + beta * uv2.x + gamma * uv3.x) * texturebuffer.width()), 0, texturebuffer.width() - 1);
					int v = std::clamp(static_cast<int>((alpha * uv1.y + beta * uv2.y + gamma * uv3.y) * texturebuffer.height()), 0, texturebuffer.height() - 1);
					double nx = alpha * n1.x + beta * n2.x + gamma * n3.x;
					double ny = alpha * n1.y + beta * n2.y + gamma * n3.y;
					double nz = alpha * n1.z + beta * n2.z + gamma * n3.z;
					if (z > depthbuffer.get(x, y)[0]) {
						depthbuffer.set(x, y, {z});
						framebuffer.set(x, y, texturebuffer.get(u, v));
					}
				}
			}
		}
	}
}


std::tuple<int, int, int, int> Rasterizer::CalcAABB(const vec2& p1, const vec2& p2, const vec2& p3) {
	int xmin, xmax, ymin, ymax;
	xmin = static_cast<int>(std::min(std::min(p1.x, p2.x), p3.x));
	xmax = static_cast<int>(std::max(std::max(p1.x, p2.x), p3.x));
	ymin = static_cast<int>(std::min(std::min(p1.y, p2.y), p3.y));
	ymax = static_cast<int>(std::max(std::max(p1.y, p2.y), p3.y));
	return std::tuple<int, int, int, int>(xmin, ymin, xmax, ymax);
}

double Rasterizer::CalcSignedArea(const vec2& p1, const vec2& p2, const vec2& p3) {
	return .5 * ((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x));
}

std::tuple<double, double, double> Rasterizer::CalcBarycentricCoordinates(const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p) {
	double total_area = CalcSignedArea(p1, p2, p3);
	double alpha = CalcSignedArea(p, p2, p3) / total_area;
	double beta = CalcSignedArea(p1, p, p3) / total_area;
	double gamma = 1 - alpha - beta;
	return std::make_tuple(alpha, beta, gamma);
}

bool Rasterizer::IsCulling(const vec2& p1, const vec2& p2, const vec2& p3) {
	return CalcSignedArea(p1, p2, p3) <= 1;
}

bool Rasterizer::IsInsideTriangle(const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p) {
	// Using cross-product to test point inclusion in a triangle

	vec2 p1p2 = p2 - p1;
	vec2 p2p3 = p3 - p2;
	vec2 p3p1 = p1 - p3;
	vec2 p1p = p - p1;
	vec2 p2p = p - p2;
	vec2 p3p = p - p3;

	int sign1 = static_cast<int>(p1p2.x * p1p.y - p1p2.y * p1p.x);
	int sign2 = static_cast<int>(p2p3.x * p2p.y - p2p3.y * p2p.x);
	int sign3 = static_cast<int>(p3p1.x * p3p.y - p3p1.y * p3p.x);

	return (sign1 > 0 && sign2 > 0 && sign3 > 0) || (sign1 < 0 && sign2 < 0 && sign3 < 0);
}
