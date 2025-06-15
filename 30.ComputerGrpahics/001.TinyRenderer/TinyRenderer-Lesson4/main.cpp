#include "Rasterizer.h"
#include "ObjLoader.h"
#include "zer0Math.h"

vec3 rotate(vec3 v) {
	constexpr double a = M_PI / 6;

	// Non-literal type, because of union
	mat3x3 Ry = {
		std::cos(a), 0, std::sin(a),
		0, 1, 0,
		-std::sin(a), 0, std::cos(a)
	};

	return Ry * v;
}

vec3 persp(vec3 v) {
	constexpr double c = 10;

	double z = v.z;
	v /= (1 - v.z / c);
	v.z = z;

	return v;
}

vec3 transform(vec3 v) {
	return persp(rotate(v));
}

void fit(vec3& v, int width, int height) {
	v.x = (v.x + 1) * width * 0.5;
	v.y = (v.y + 1) * height * 0.5;
	v.z = (v.z + 1) * 255 * 0.5;
}

void perspective_model() {
	constexpr int width = 1024;
	constexpr int height = 1024;

	TGAImage framebuffer(width, height, TGAImage::RGB);
	TGAImage depthbuffer(width, height, TGAImage::GRAYSCALE);
	TGAImage texturebuffer;
	texturebuffer.read_tga_file("../models/african_head/african_head_diffuse.tga");

	Rasterizer::Culling = true;
	Rasterizer::Wireframe = false;

	std::string path = "../models/african_head/";
	std::string filename = "african_head";
	mesh obj = ObjLoader::LoadObj(path + filename + ".obj", false);

	for (int i = 0; i < obj.vertex_indices.size(); i += 3) {
		vec3 v1 = transform(obj.vertices[obj.vertex_indices[i]]);
		vec3 v2 = transform(obj.vertices[obj.vertex_indices[i + 1]]);
		vec3 v3 = transform(obj.vertices[obj.vertex_indices[i + 2]]);
		vec2 uv1 = obj.uvs[obj.uv_indcies[i]];
		vec2 uv2 = obj.uvs[obj.uv_indcies[i + 1]];
		vec2 uv3 = obj.uvs[obj.uv_indcies[i + 2]];

		fit(v1, width, height);
		fit(v2, width, height);
		fit(v3, width, height);

		Rasterizer::Triangle(v1, v2, v3,
							 uv1, uv2, uv3,
							 framebuffer, depthbuffer,
							 texturebuffer);
	}

	depthbuffer.write_tga_file("../_results/Lesson4-african_head_depthbuffer.tga");
	framebuffer.write_tga_file("../_results/Lesson4-african_head_perspective.tga");
}

void homework() {
	constexpr int width = 1024;
	constexpr int height = 1024;

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
		vec2 uv1 = obj.uvs[obj.uv_indcies[i]];
		vec2 uv2 = obj.uvs[obj.uv_indcies[i + 1]];
		vec2 uv3 = obj.uvs[obj.uv_indcies[i + 2]];

		fit(v1, width, height);
		fit(v2, width, height);
		fit(v3, width, height);

		Rasterizer::Triangle(v1, v2, v3,
							 uv1, uv2, uv3,
							 framebuffer, depthbuffer,
							 texturebuffer);
	}

	depthbuffer.write_tga_file("../_results/Lesson4-diablo3_pose_depthbuffer.tga");
	framebuffer.write_tga_file("../_results/Lesson4-diablo3_pose_perspective.tga");
}

int main() {
	std::cout << "===== Lesson 4 =====" << std::endl << std::endl;

	perspective_model();
	homework();
}
