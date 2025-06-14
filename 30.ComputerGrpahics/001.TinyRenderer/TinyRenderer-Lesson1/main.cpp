#include "Timer.h"
#include "ObjLoader.h"
#include "Rasterizer.h"

using namespace zer0;

void draw_triangle() {
	TGAImage framebuffer(64, 64, TGAImage::RGB);

	std::cout << "Draw Triangle" << std::endl;
	int ax = 7, ay = 3;
	int bx = 12, by = 37;
	int cx = 62, cy = 53;

	vec2 p1(7, 3);
	vec2 p2(12, 37);
	vec2 p3(62, 53);

	Rasterizer::Triangle(p1, p2, p3, framebuffer, TGAColor::blue);

	framebuffer.write_tga_file("../_results/Lesson1-triangle.tga");
}

void speed_test() {
	TGAImage framebuffer(64, 64, TGAImage::RGB);
	TGAImage framebuffer2(64, 64, TGAImage::RGB);

	// if version
	std::cout << "Draw line(if)" << std::endl;
	Timer timer;
	timer.Start();
	for (int i = 0; i < (1 << 24); ++i) {
		vec2 p1(rand() % 64, rand() % 64);
		vec2 p2(rand() % 64, rand() % 64);
		TGAColor rnd((unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255));
		Rasterizer::Line_With_If(p1, p2, framebuffer, rnd);
	}
	timer.Stop();
	timer.Display();
	framebuffer.write_tga_file("../_results/Lesson1-speedtest_with_if.tga");

	// without if version (more fast)
	std::cout << "Draw line(without if)" << std::endl;
	timer.Start();
	for (int i = 0; i < (1 << 24); ++i) {
		vec2 p1(rand() % 64, rand() % 64);
		vec2 p2(rand() % 64, rand() % 64);
		TGAColor rnd((unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255));
		Rasterizer::Line_Without_If(p1, p2, framebuffer2, rnd);
	}
	timer.Stop();
	timer.Display();
	framebuffer2.write_tga_file("../_results/Lesson1-speedtest_without_if.tga");
}

void homework() {
	constexpr int width = 1024;
	constexpr int height = 1024;

	TGAImage framebuffer(width, height, TGAImage::RGB);

	std::string path = "../models/";
	//std::string filename = "diablo3_pose";
	std::string filename = "african_head";
	std::pair<std::vector<vec3>, std::vector<Face>> obj = ObjLoader::LoadObj(path + filename + ".obj");

	Timer timer;
	timer.Start();

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

		Rasterizer::Triangle(v1, v2, v3, framebuffer, TGAColor::red);
	}

	for (int i = 0; i < obj.first.size(); ++i) {
		vec3& v = obj.first[i];

		int x = static_cast<int>(v.x * width);
		int y = static_cast<int>(v.y * width);

		framebuffer.set(x, y, TGAColor::white);
	}

	timer.Stop();

	std::string name = "../_results/Lesson1-" + filename + ".tga";
	framebuffer.write_tga_file(name.c_str());
	std::cout << "Render finished in " << timer.ElapsedSecond() << " seconds";
}

int main(int argc, char** argv) {
	std::srand(static_cast<unsigned int>(std::time({})));
	std::cout << std::fixed;

	Rasterizer::Culling = false;
	Rasterizer::Wireframe = true;

	//draw_triangle();
	//speed_test();
	homework();

	return 0;
}
