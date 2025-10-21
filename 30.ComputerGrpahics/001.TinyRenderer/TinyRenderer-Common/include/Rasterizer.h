#pragma once

#include <algorithm>
#include <vector>

#include "tgaimage.h"
#include "zer0Math.h"
#include "Geometry.h"
#include "IShader.h"

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

	// Draw depthbuffer (only) - Chatper 3
	static void Triangle_With_DepthColor(const vec3& p1, const vec3& p2, const vec3& p3, TGAImage& framebuffer);
	// Draw full-colored triangles
	static void Triangle_With_FullColored(const vec2& p1, const vec2& p2, const vec2& p3, TGAImage& framebuffer, const TGAColor& color1, const TGAColor& color2, const TGAColor& color3);

	// Draw frame buffer with color
	static void Triangle(const vec2& p1, const vec2& p2, const vec2& p3, TGAImage& framebuffer, const TGAColor& color);

	// Draw depthbuffer & frame buffer with color
	static void Triangle(
		const vec3& p1, const vec3& p2, const vec3& p3,
		TGAImage& framebuffer, TGAImage& depthbuffer,
		const TGAColor& color
	);

	// Draw framebuffer using double depthbuffer
	static void Triangle(
		const vec3& p1, const vec3& p2, const vec3& p3,
		TGAImage& framebuffer, std::vector<double>& depthbuffer,
		const TGAColor& color
	);

	// Draw with shader (without normal)
	static void Triangle(
		const mesh& model, IShader& shader,
		TGAImage& framebuffer, std::vector<double> depthbuffer
	);

	// Draw with shader with smooth normal
	static void Triangle_With_Smooth_Normal(
		const mesh& model, IShader& shader,
		TGAImage& framebuffer, std::vector<double> depthbuffer
	);

	// Draw with shader with normal map
	static void Triangle_With_Normal_Mapping(
		const mesh& model, IShader& shader,
		TGAImage& framebuffer, std::vector<double> depthbuffer,
		const TGAImage& normalmap
	);

	// Draw with shader with normal map & texture
	static void Triangle_With_Normal_Mapping_And_Texture(
		const mesh& model, IShader& shader,
		TGAImage& framebuffer, std::vector<double> depthbuffer,
		const TGAImage& diff_texture, const TGAImage& spec_texture,
		const TGAImage& normalmap
	);

private:
	static std::tuple<int, int, int, int> CalcAABB(const vec2& p1, const vec2& p2, const vec2& p3);
	static double CalcSignedArea(const vec2& p1, const vec2& p2, const vec2& p3);
	static std::tuple<double, double, double> CalcBarycentricCoordinates(const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p);

	/// <summary>
	/// Backface-culling & Area < 1 culling
	/// </summary>
	static bool IsCulling(const vec2& p1, const vec2& p2, const vec2& p3);
	static bool IsInsideTriangle(const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p);
	static bool IsInsideTriangle_BarycentricArea(const vec2& p1, const vec2& p2, const vec2& p3, const vec2& p);

public:
	static inline bool Culling = true;
	static inline bool Wireframe = false;
};

