#include "tgaimage.h"
#include "ObjLoader.h"
#include "Rasterizer.h"

void Depth_Rasterization() {
	constexpr int width = 1024;
	constexpr int height = 1024;

	TGAImage framebuffer(width, height, TGAImage::RGB);
	TGAImage depthbuffer(width, height, TGAImage::GRAYSCALE);

	std::string path = "../models/";
	std::string filename = "african_head";
	//std::string filename = "diablo3_pose";
	std::pair<std::vector<Vec3>, std::vector<Face>> obj = ObjLoader::LoadObj(path + filename + ".obj");

	for (int i = 0; i < obj.second.size(); ++i) {
		Face& f = obj.second[i];

		Vec3& v1 = obj.first[f.V1];
		Vec3& v2 = obj.first[f.V2];
		Vec3& v3 = obj.first[f.V3];

		int ax = v1.X * width;
		int ay = v1.Y * height;
		int az = v1.Z * 255;
		int bx = v2.X * width;
		int by = v2.Y * height;
		int bz = v2.Z * 255;
		int cx = v3.X * width;
		int cy = v3.Y * height;
		int cz = v3.Z * 255;

		TGAColor rnd;
		rnd[0] = std::rand() % 255;
		rnd[1] = std::rand() % 255;
		rnd[2] = std::rand() % 255;
		Rasterizer::Triangle(ax, ay, az, bx, by, bz, cx, cy, cz, framebuffer, depthbuffer, rnd);
	}

	depthbuffer.write_tga_file("../_results/Lesson3_african_head_depthbuffer.tga");
	framebuffer.write_tga_file("../_results/Lesson3_african_head.tga");
}

int main() {
	Depth_Rasterization();
}
