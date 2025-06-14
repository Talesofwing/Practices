#include "tgaimage.h"
#include "ObjLoader.h"
#include "Rasterizer.h"
#include "zer0Math.h"

void depth_rasterization() {
	constexpr int width = 1024;
	constexpr int height = 1024;

	TGAImage framebuffer(width, height, TGAImage::RGB);
	TGAImage depthbuffer(width, height, TGAImage::GRAYSCALE);

	std::string path = "../models/";
	//std::string filename = "african_head";
	std::string filename = "diablo3_pose";
	std::pair<std::vector<vec3>, std::vector<Face>> obj = ObjLoader::LoadObj(path + filename + ".obj");

	for (int i = 0; i < obj.second.size(); ++i) {
		Face& f = obj.second[i];

		vec3 v1 = obj.first[f.V1];
		vec3 v2 = obj.first[f.V2];
		vec3 v3 = obj.first[f.V3];

		v1.x *= width;
		v1.y *= height;
		v1.z *= 255;
		v2.x *= width;
		v2.y *= height;
		v2.z *= 255;
		v3.x *= width;
		v3.y *= height;
		v3.z *= 255;

		TGAColor rnd((unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255));

		Rasterizer::Triangle(v1, v2, v3, framebuffer, depthbuffer, rnd);
	}

	//depthbuffer.write_tga_file("../_results/Lesson3-african_head_depthbuffer.tga");
	//framebuffer.write_tga_file("../_results/Lesson3-african_head.tga");

	depthbuffer.write_tga_file("../_results/Lesson3-diablo3_pose_depthbuffer.tga");
	framebuffer.write_tga_file("../_results/Lesson3-diablo3_pose.tga");
}

int main() {
	depth_rasterization();
}
