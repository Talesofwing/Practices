#include "Rasterizer.h"
#include "ObjLoader.h"
#include "zer0Math.h"

constexpr int width = 1024;
constexpr int height = 1024;

vec3 eye(-1, 0, 2);
vec3 up(0, 1, 0);
vec3 center(0, 0, 0);

vec3 view(vec3 v) {
	vec3 z = (eye - center).normalize();	// right-handed coordinate
	vec3 x = cross(up, z).normalize();
	vec3 y = cross(z, x).normalize();
	mat4x4 m {
		x.x, x.y, x.z, -dot(x, center),
		y.x, y.y, y.z, -dot(y, center),
		z.x, z.y, z.z, -dot(z, center),
		0, 0, 0., 1
	};

	return m * v;
}

vec4 proj(vec3 v) {
	double f = (eye - center).length();
	mat4x4 m {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, -1 / f, 1
	};

	return m * v;
}

vec3 ndc(vec4 v) {
	v /= v.w;
	return v;
}

vec3 viewport(vec4 v) {
	mat4x4 m {
		width * 0.5, 0, 0, width * 0.5,
		0, height * 0.5, 0, height * 0.5,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	return m * v;
}

vec3 transform(vec3 v) {
	return viewport(ndc(proj(view(v))));
}

void perspective_mode() {
	TGAImage framebuffer(width, height, TGAImage::RGB);
	TGAImage depthbuffer(width, height, TGAImage::GRAYSCALE);

	std::string path = "../models/african_head/";
	std::string filename = "african_head";
	mesh obj = ObjLoader::LoadObj(path + filename + ".obj", false);

	for (int i = 0; i < obj.vertex_indices.size(); i += 3) {
		vec3 v1 = transform(obj.vertices[obj.vertex_indices[i]]);
		vec3 v2 = transform(obj.vertices[obj.vertex_indices[i + 1]]);
		vec3 v3 = transform(obj.vertices[obj.vertex_indices[i + 2]]);

		TGAColor rnd((unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255));

		Rasterizer::Triangle(v1, v2, v3, framebuffer, depthbuffer, rnd);
	}

	depthbuffer.write_tga_file("../_results/Lesson5-african_head_depthbuffer.tga");
	framebuffer.write_tga_file("../_results/Lesson5-african_head_perspective.tga");

	TGAImage framebuffer2(width, height, TGAImage::RGB);
	TGAImage depthbuffer2(width, height, TGAImage::GRAYSCALE);

	path = "../models/diablo3_pose/";
	filename = "diablo3_pose";
	obj = ObjLoader::LoadObj(path + filename + ".obj", false);

	for (int i = 0; i < obj.vertex_indices.size(); i += 3) {
		vec3 v1 = transform(obj.vertices[obj.vertex_indices[i]]);
		vec3 v2 = transform(obj.vertices[obj.vertex_indices[i + 1]]);
		vec3 v3 = transform(obj.vertices[obj.vertex_indices[i + 2]]);

		TGAColor rnd((unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255), (unsigned char)(rand() % 255));

		Rasterizer::Triangle(v1, v2, v3, framebuffer2, depthbuffer2, rnd);
	}

	depthbuffer2.write_tga_file("../_results/Lesson5-diablo3_pose_depthbuffer.tga");
	framebuffer2.write_tga_file("../_results/Lesson5-diablo3_pose_perspective.tga");
}

int main() {
	std::cout << "===== Lesson 5 =====" << std::endl << std::endl;

	perspective_mode();
}
