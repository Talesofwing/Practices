#include "LineDrawer.h"
#include "Rasterizer.h"
#include "ObjLoader.h"

void Triangle() {
	constexpr int width = 128;
	constexpr int height = 128;

	TGAImage framebuffer(width, height, TGAImage::RGB);

	LineDrawer::DrawTriangle(45, 60, 35, 100, 7, 45, framebuffer, TGAColor::red);
	LineDrawer::DrawTriangle(120, 35, 90, 5, 45, 110, framebuffer, TGAColor::white);
	LineDrawer::DrawTriangle(115, 83, 80, 90, 85, 120, framebuffer, TGAColor::green);

	framebuffer.flip_vertically();
	framebuffer.write_tga_file("../_results/Lesson2.tga");
}

void Triangle_Rasterization() {
	constexpr int width = 128;
	constexpr int height = 128;

	TGAImage framebuffer(width, height, TGAImage::RGB);

	// Will render
	Rasterizer::Triangle_Old(45, 60, 35, 100, 7, 45, framebuffer, TGAColor::red);

	// Won't render (backface-culling)
	Rasterizer::Triangle_Old(120, 35, 90, 5, 45, 110, framebuffer, TGAColor::white);
	Rasterizer::Triangle_Old(115, 83, 80, 90, 85, 120, framebuffer, TGAColor::green);

	framebuffer.flip_vertically();
	framebuffer.write_tga_file("../_results/Lesson2_Rasterization.tga");
}

void Triangle_Rasterization_Modern() {
	constexpr int width = 128;
	constexpr int height = 128;

	TGAImage framebuffer(width, height, TGAImage::RGB);

	Rasterizer::Triangle(45, 60, 35, 100, 7, 45, framebuffer, TGAColor::red);

	Rasterizer::Triangle(120, 35, 90, 5, 45, 110, framebuffer, TGAColor::white);
	Rasterizer::Triangle(115, 83, 80, 90, 85, 120, framebuffer, TGAColor::green);

	framebuffer.flip_vertically();
	framebuffer.write_tga_file("../_results/Lesson2_Rasterization_Modern.tga");
}

void Triangle_Rasterization_Head() {
	constexpr int width = 1024;
	constexpr int height = 1024;

	TGAImage framebuffer(width, height, TGAImage::RGB);

	std::string path = "../models/";
	std::string filename = "african_head";
	std::pair<std::vector<Vec3>, std::vector<Face>> obj = ObjLoader::LoadObj(path + filename + ".obj");

	for (int i = 0; i < obj.second.size(); ++i) {
		Face& f = obj.second[i];

		Vec3& v1 = obj.first[f.V1];
		Vec3& v2 = obj.first[f.V2];
		Vec3& v3 = obj.first[f.V3];

		int ax = v1.X * width;
		int ay = v1.Y * height;
		int bx = v2.X * width;
		int by = v2.Y * height;
		int cx = v3.X * width;
		int cy = v3.Y * height;

		TGAColor rnd;
		rnd.r = std::rand() % 255;
		rnd.g = std::rand() % 255;
		rnd.b = std::rand() % 255;
		Rasterizer::Triangle(ax, ay, bx, by, cx, cy, framebuffer, rnd);
	}

	framebuffer.flip_vertically();
	framebuffer.write_tga_file("../_results/Lesson2_Rasterization_Modern_Head.tga");
}

int main() {
	std::srand(std::time({}));

	//Triangle();
	//Triangle_Rasterization();
	//Triangle_Rasterization_Modern();
	Triangle_Rasterization_Head();
}
