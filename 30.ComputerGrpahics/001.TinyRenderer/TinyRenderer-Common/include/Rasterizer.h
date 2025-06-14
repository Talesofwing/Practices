#pragma once

#include <algorithm>

#include "tgaimage.h"
#include "zer0Math.h"
#include "Geometry.h"

using namespace zer0;

class Rasterizer {
	Rasterizer() = delete;
	Rasterizer(const Rasterizer&) = delete;

	Rasterizer& operator=(const Rasterizer&) = delete;

public:
	// Line
	static void Line_Without_If(vec2 start, vec2 end, TGAImage& framebuffer, const TGAColor& color);
	static void Line_With_If(vec2 start, vec2 end, TGAImage& framebuffer, const TGAColor& color);

	// Triangle
	static void Triangle_Old(vec2 p1, vec2 p2, vec2 p3, TGAImage& framebuffer, const TGAColor& color);
	static void Triangle(const vec2& p1, const vec2& p2, const vec2& p3, TGAImage& framebuffer, const TGAColor& color);
	static void Triangle(const vec3& p1, const vec3& p2, const vec3& p3, TGAImage& framebuffer, TGAImage& depthbuffer, const TGAColor& color);

	static void Triangle(
		const vec3& p1, const vec3& p2, const vec3& p3,
		const vec2& uv1, const vec2& uv2, const vec2& uv3,
		TGAImage& framebuffer, TGAImage& depthbuffer,
		const TGAImage& texturebuffer);

	static void Triangle(
		const vec3& p1, const vec3& p2, const vec3& p3,
		const vec2& uv1, const vec2& uv2, const vec2& uv3,
		const vec3& n1, const vec3& n2, const vec3& n3,
		TGAImage& framebuffer, TGAImage& depthbuffer,
		const TGAImage& texturebuffer);

private:
	static std::tuple<int, int, int, int> CalcAABB(const vec2& p1, const vec2& p2, const vec2& p3);
	static double CalcSignedArea(const vec2& p1, const vec2& p2, const vec2& p3);
	static std::tuple<double, double, double> CalcBarycentricCoordinates(const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p);

	/// <summary>
	/// Backface-culling & Area < 1 culling
	/// </summary>
	static bool IsCulling(const vec2& p1, const vec2& p2, const vec2& p3);
	static bool IsInsideTriangle(const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p);

public:
	static inline bool Culling = true;
	static inline bool Wireframe = false;
};

