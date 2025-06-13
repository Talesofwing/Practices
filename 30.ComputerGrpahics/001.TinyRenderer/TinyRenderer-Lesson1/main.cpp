#include "Timer.h"
#include "ObjLoader.h"
#include "LineDrawer.h"

void draw_triangle() {
	TGAImage framebuffer(64, 64, TGAImage::RGB);

	std::cout << "Draw Triangle" << std::endl;
	int ax = 7, ay = 3;
	int bx = 12, by = 37;
	int cx = 62, cy = 53;

	LineDrawer::DrawTriangle(ax, ay,
							 bx, by,
							 cx, cy,
							 framebuffer, TGAColor::blue);

	framebuffer.write_tga_file("../_results/Lesson1-Triangle.tga");
}

void speed_test() {
	TGAImage framebuffer(64, 64, TGAImage::RGB);

	// if version
	std::cout << "Draw line(if)" << std::endl;
	Timer timer;
	timer.Start();
	for (int i = 0; i < (1 << 24); ++i) {
		int ax = rand() % 64, ay = rand() % 64;
		int bx = rand() % 64, by = rand() % 64;
		LineDrawer::DrawLine_Slow(ax, ay, bx, by, framebuffer, {(unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255)});
	}
	timer.Stop();
	timer.Display();
	framebuffer.write_tga_file("../_results/Lesson1.tga");

	// without if version (more fast)
	std::cout << "Draw line(without if)" << std::endl;
	framebuffer.clear();
	timer.Start();
	for (int i = 0; i < (1 << 24); ++i) {
		int ax = rand() % 64, ay = rand() % 64;
		int bx = rand() % 64, by = rand() % 64;
		LineDrawer::DrawLine_Fast(ax, ay, bx, by, framebuffer, {(unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255)});
	}
	timer.Stop();
	timer.Display();
	framebuffer.write_tga_file("../_results/Lesson1.tga");
}

void Homework() {
	constexpr int width = 1024;
	constexpr int height = 1024;

	TGAImage framebuffer(width, height, TGAImage::RGB);

	std::string path = "../models/";
	//std::string filename = "diablo3_pose";
	std::string filename = "african_head";
	std::pair<std::vector<Vec3>, std::vector<Face>> obj = ObjLoader::LoadObj(path + filename + ".obj");

	Timer timer;
	timer.Start();

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

		LineDrawer::DrawTriangle(ax, ay,
								 bx, by,
								 cx, cy,
								 framebuffer, TGAColor::red);
	}

	for (int i = 0; i < obj.first.size(); ++i) {
		Vec3& v = obj.first[i];

		int x = v.X * width;
		int y = v.Y * width;

		framebuffer.set(x, y, TGAColor::white);
	}

	timer.Stop();

	framebuffer.flip_vertically();

	std::string name = "../_results/Lesson1-" + filename + ".tga";
	framebuffer.write_tga_file(name.c_str());
	std::cout << "Render finished in " << timer.ElapsedSecond() << " seconds";
}

int main(int argc, char** argv) {
	std::srand(std::time({}));
	std::cout << std::fixed;

	//draw_triangle();
	//speed_test();
	Homework();

	return 0;
}
