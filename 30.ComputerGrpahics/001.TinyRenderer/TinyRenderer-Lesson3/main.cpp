#include "tgaimage.h"
#include "ObjLoader.h"
#include "Rasterizer.h"
#include "zer0Math.h"

void depth_rasterization() {
	constexpr int width = 1024;
	constexpr int height = 1024;

	TGAImage framebuffer(width, height, TGAImage::RGB);
	TGAImage depthbuffer(width, height, TGAImage::GRAYSCALE);

	//std::string path = "../models/african_head/";
	 std::string path = "../models/diablo3_pose/";
	//std::string filename = "african_head";
	std::string filename = "diablo3_pose";
	mesh obj = ObjLoader::LoadObj(path + filename + ".obj");

	for (int i = 0; i < obj.vertex_indices.size(); i += 3) {
		vec3 v1 = obj.vertices[obj.vertex_indices[i]];
		vec3 v2 = obj.vertices[obj.vertex_indices[i + 1]];
		vec3 v3 = obj.vertices[obj.vertex_indices[i + 2]];

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

void texture_rasterization() {
	constexpr int width = 1024;
	constexpr int height = 1024;

	TGAImage framebuffer(width, height, TGAImage::RGB);
	TGAImage depthbuffer(width, height, TGAImage::GRAYSCALE);
	TGAImage texturebuffer;
	texturebuffer.read_tga_file("../models/african_head/african_head_diffuse.tga");

	std::string path = "../models/african_head/";
	std::string filename = "african_head";
	mesh obj = ObjLoader::LoadObj(path + filename + ".obj");

	for (int i = 0; i < obj.vertex_indices.size(); i += 3) {
		vec3 v1 = obj.vertices[obj.vertex_indices[i]];
		vec3 v2 = obj.vertices[obj.vertex_indices[i + 1]];
		vec3 v3 = obj.vertices[obj.vertex_indices[i + 2]];
		vec2 uv1 = obj.uvs[obj.uv_indcies[i]];
		vec2 uv2 = obj.uvs[obj.uv_indcies[i + 1]];
		vec2 uv3 = obj.uvs[obj.uv_indcies[i + 2]];

		v1.x *= width;
		v1.y *= height;
		v1.z *= 255;
		v2.x *= width;
		v2.y *= height;
		v2.z *= 255;
		v3.x *= width;
		v3.y *= height;
		v3.z *= 255;

		Rasterizer::Triangle(v1, v2, v3,
							 uv1, uv2, uv3,
							 framebuffer, depthbuffer,
							 texturebuffer);
	}

	depthbuffer.write_tga_file("../_results/Lesson3-african_head_depthbuffer.tga");
	framebuffer.write_tga_file("../_results/Lesson3-african_head_texture.tga");
}

int main() {
	std::cout << "===== Lesson 3 =====" << std::endl << std::endl;

	depth_rasterization();
	texture_rasterization();
}
