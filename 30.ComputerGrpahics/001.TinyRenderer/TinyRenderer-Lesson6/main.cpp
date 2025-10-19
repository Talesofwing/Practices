#include <cmath>

#include "Rasterizer.h"
#include "ObjLoader.h"
#include "zer0Math.h"

constexpr int width = 1024;
constexpr int height = 1024;

vec3 eye(-1, 0, 2);
vec3 up(0, 1, 0);
vec3 lookAt(0, 0, 0);

void perspective_mode() {
	TGAImage framebuffer(width, height, TGAImage::RGB);
	std::vector<double> depthbuffer(width * height, std::numeric_limits<double>::lowest());

	std::string path = "../models/african_head/";
	std::string filename = "african_head";
	mesh obj = ObjLoader::LoadObj(path + filename + ".obj", false);

	for (int i = 0; i < obj.vertex_indices.size(); i += 3) {
		vec3 v1 = transform(obj.vertices[obj.vertex_indices[i]], eye, up, lookAt, width, height);
		vec3 v2 = transform(obj.vertices[obj.vertex_indices[i + 1]], eye, up, lookAt, width, height);
		vec3 v3 = transform(obj.vertices[obj.vertex_indices[i + 2]], eye, up, lookAt, width, height);

		TGAColor rnd((unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255));

		Rasterizer::Triangle(v1, v2, v3, framebuffer, depthbuffer, rnd);
	}

	framebuffer.write_tga_file("../_results/Lesson6/african_head_perspective.tga");

	TGAImage framebuffer2(width, height, TGAImage::RGB);
	std::vector<double> depthbuffer2(width * height, std::numeric_limits<double>::lowest());

	std::string path2 = "../models/diablo3_pose/";
	std::string filename2 = "diablo3_pose";
	mesh obj2 = ObjLoader::LoadObj(path2 + filename2 + ".obj", false);

	for (int i = 0; i < obj2.vertex_indices.size(); i += 3) {
		vec3 v1 = transform(obj2.vertices[obj2.vertex_indices[i]], eye, up, lookAt, width, height);
		vec3 v2 = transform(obj2.vertices[obj2.vertex_indices[i + 1]], eye, up, lookAt, width, height);
		vec3 v3 = transform(obj2.vertices[obj2.vertex_indices[i + 2]], eye, up, lookAt, width, height);

		TGAColor rnd((unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255));

		Rasterizer::Triangle(v1, v2, v3, framebuffer2, depthbuffer2, rnd);
	}

	framebuffer2.write_tga_file("../_results/Lesson6/diablo3_pose_perspective.tga");
}

void draw_triangle() {
	Rasterizer::Culling = false;

	TGAImage framebuffer(width, height, TGAImage::RGB);
	std::vector<double> depthbuffer(width * height, std::numeric_limits<double>::lowest());

	vec3 v1(0, 0, -2);
	vec3 v2(0, 1, -1);
	vec3 v3(0.5, 0.5, -5);
	v1 = transform(v1, eye, up, lookAt, width, height);
	v2 = transform(v2, eye, up, lookAt, width, height);
	v3 = transform(v3, eye, up, lookAt, width, height);
	Rasterizer::Triangle(v1, v2, v3, framebuffer, depthbuffer, TGAColor::blue);

	vec3 v4(0, 0, -5);
	vec3 v5(0, 1, -3);
	vec3 v6(0.5, 0.5, -10);
	v4 = transform(v4, eye, up, lookAt, width, height);
	v5 = transform(v5, eye, up, lookAt, width, height);
	v6 = transform(v6, eye, up, lookAt, width, height);
	Rasterizer::Triangle(v4, v5, v6, framebuffer, depthbuffer, TGAColor::red);

	framebuffer.write_tga_file("../_results/Lesson6/triangle.tga");
}

int main() {
	std::cout << "===== Lesson 6 =====" << std::endl << std::endl;

	perspective_mode();
	draw_triangle();
}
