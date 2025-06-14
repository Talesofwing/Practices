#include "Rasterizer.h"
#include "ObjLoader.h"
#include "zer0Math.h"

using namespace zer0;

void triangle_wireframe() {
	constexpr int width = 128;
	constexpr int height = 128;

	TGAImage framebuffer(width, height, TGAImage::RGB);

	Rasterizer::Culling = false;
	Rasterizer::Wireframe = true;

	Rasterizer::Triangle({45, 60}, {35, 100}, {7, 45}, framebuffer, TGAColor::red);
	Rasterizer::Triangle({120, 35}, {90, 5}, {45, 110}, framebuffer, TGAColor::white);
	Rasterizer::Triangle({115, 83}, {80, 90}, {85, 120}, framebuffer, TGAColor::green);

	framebuffer.write_tga_file("../_results/Lesson2-triangle.tga");
}

void triangle_rasterization() {
	constexpr int width = 128;
	constexpr int height = 128;

	TGAImage framebuffer(width, height, TGAImage::RGB);

	// Will render
	Rasterizer::Triangle_Old({45, 60}, {35, 100}, {7, 45}, framebuffer, TGAColor::red);

	// Won't render (backface-culling)
	Rasterizer::Triangle_Old({120, 35}, {90, 5}, {45, 110}, framebuffer, TGAColor::white);
	Rasterizer::Triangle_Old({115, 83}, {80, 90}, {85, 120}, framebuffer, TGAColor::green);

	framebuffer.write_tga_file("../_results/Lesson2-rasterization.tga");
}

void triangle_rasterization_modern() {
	constexpr int width = 128;
	constexpr int height = 128;

	TGAImage framebuffer(width, height, TGAImage::RGB);

	Rasterizer::Triangle({45, 60}, {35, 100}, {7, 45}, framebuffer, TGAColor::red);

	Rasterizer::Triangle({120, 35}, {90, 5}, {45, 110}, framebuffer, TGAColor::white);
	Rasterizer::Triangle({115, 83}, {80, 90}, {85, 120}, framebuffer, TGAColor::green);

	framebuffer.write_tga_file("../_results/Lesson2-rasterization_modern.tga");
}

void triangle_rasterization_model() {
	constexpr int width = 1024;
	constexpr int height = 1024;

	TGAImage framebuffer(width, height, TGAImage::RGB);

	std::string path = "../models/";
	std::string filename = "african_head";
	std::pair<std::vector<vec3>, std::vector<Face>> obj = ObjLoader::LoadObj(path + filename + ".obj");

	for (int i = 0; i < obj.second.size(); ++i) {
		Face& f = obj.second[i];

		vec3 v1 = obj.first[f.V1];
		vec3 v2 = obj.first[f.V2];
		vec3 v3 = obj.first[f.V3];

		v1.x *= width;
		v1.y *= height;
		v2.x *= width;
		v2.y *= height;
		v3.x *= width;
		v3.y *= height;

		TGAColor rnd((unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255));

		Rasterizer::Triangle(v1, v2, v3, framebuffer, rnd);
	}

	framebuffer.write_tga_file("../_results/Lesson2-rasterization_african_head.tga");
}

int main() {
	std::srand(static_cast<unsigned int>(std::time({})));

	triangle_wireframe();
	triangle_rasterization();
	triangle_rasterization_modern();
	triangle_rasterization_model();
}
