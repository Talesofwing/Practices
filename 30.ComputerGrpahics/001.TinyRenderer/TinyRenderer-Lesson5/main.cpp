#include "Rasterizer.h"
#include "ObjLoader.h"
#include "zer0Math.h"

constexpr int width = 1024;
constexpr int height = 1024;

vec3 world(vec3 v) {
	constexpr double theta = M_PI / 6;

	mat3x3 m = {
		std::cos(theta), 0, std::sin(theta),
		0, 1, 0,
		-std::sin(theta), 0, std::cos(theta)
	};

	return m * v;
}

vec3 proj(vec3 v) {
	constexpr double c = 5;

	v.x /= (1 - v.z / c);
	v.y /= (1 - v.z / c);

	return v;
}

vec3 viewport(vec3 v) {
	v.x = (v.x + 1) * 0.5 * width;
	v.y = (v.y + 1) * 0.5 * height;
	v.z = (v.z + 1) * 0.5 * 255;

	return v;
}

vec3 transform(vec3 v) {
	return viewport(proj(world(v)));
}

void render() {
	TGAImage framebuffer(width, height, TGAImage::RGB);
	TGAImage depthbuffer(width, height, TGAImage::GRAYSCALE);

	Rasterizer::Culling = true;
	Rasterizer::Wireframe = false;

	std::string path = "../models/african_head/";
	std::string filename = "african_head";
	mesh obj = ObjLoader::LoadObj(path + filename + ".obj", false);

	for (int i = 0; i < obj.vertex_indices.size(); i += 3) {
		vec3 v1 = transform(obj.vertices[obj.vertex_indices[i]]);
		vec3 v2 = transform(obj.vertices[obj.vertex_indices[i + 1]]);
		vec3 v3 = transform(obj.vertices[obj.vertex_indices[i + 2]]);
		vec2 uv1 = obj.uvs[obj.uv_indices[i]];
		vec2 uv2 = obj.uvs[obj.uv_indices[i + 1]];
		vec2 uv3 = obj.uvs[obj.uv_indices[i + 2]];

		TGAColor rnd((unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255));

		Rasterizer::Triangle(v1, v2, v3,
							 framebuffer, depthbuffer,
							 rnd);
	}

	depthbuffer.write_tga_file("../_results/Lesson5/african_head_depthbuffer.tga");
	framebuffer.write_tga_file("../_results/Lesson5/african_head_perspective.tga");
}

void homework() {
	TGAImage framebuffer(width, height, TGAImage::RGB);
	TGAImage depthbuffer(width, height, TGAImage::GRAYSCALE);
	TGAImage texturebuffer;
	texturebuffer.read_tga_file("../models/diablo3_pose/diablo3_pose_diffuse.tga");

	Rasterizer::Culling = true;
	Rasterizer::Wireframe = false;

	std::string path = "../models/diablo3_pose/";
	std::string filename = "diablo3_pose";
	mesh obj = ObjLoader::LoadObj(path + filename + ".obj", false);

	for (int i = 0; i < obj.vertex_indices.size(); i += 3) {
		vec3 v1 = transform(obj.vertices[obj.vertex_indices[i]]);
		vec3 v2 = transform(obj.vertices[obj.vertex_indices[i + 1]]);
		vec3 v3 = transform(obj.vertices[obj.vertex_indices[i + 2]]);
		vec2 uv1 = obj.uvs[obj.uv_indices[i]];
		vec2 uv2 = obj.uvs[obj.uv_indices[i + 1]];
		vec2 uv3 = obj.uvs[obj.uv_indices[i + 2]];

		TGAColor rnd((unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255));

		Rasterizer::Triangle(v1, v2, v3,
							 framebuffer, depthbuffer,
							 rnd);
	}

	depthbuffer.write_tga_file("../_results/Lesson5/diablo3_pose_depthbuffer.tga");
	framebuffer.write_tga_file("../_results/Lesson5/diablo3_pose_perspective.tga");
}

int main() {
	std::cout << "===== Lesson 5 =====" << std::endl << std::endl;

	render();
	homework();
}
