#include "Rasterizer.h"
#include "ObjLoader.h"
#include "zer0Math.h"
#include "IShader.h"

constexpr int width = 1024;
constexpr int height = 1024;

vec3 eye(-1, 0, 2);
vec3 up(0, 1, 0);
vec3 center(0, 0, 0);

vec3 light_dir(1, 1, 1);

struct GouraudShader : public IShader {
	vec3 varying_intensity;

	virtual vec4 vertex(int nthvert, const mesh& model, int vert_index) {
		vec4 p = model.vertices[model.vertex_indices[vert_index]];
		vec3 n = model.normals[model.normals_indices[vert_index]];
		varying_intensity[nthvert] = std::max(0.0, dot(n, light_dir));

		return transform(p, eye, up, center, width, height);
	}

	virtual bool fragment(double alpha, double beta, double gamma, TGAColor& color) {
		float intensity = varying_intensity[0] * alpha + varying_intensity[1] * beta + varying_intensity[2] * gamma;
		color[0] = 255 * intensity;
		color[1] = 255 * intensity;
		color[2] = 255 * intensity;

		return false;
	}
};

void render() {
	light_dir.normalize();

	TGAImage framebuffer(width, height, TGAImage::RGB);
	TGAImage depthbuffer(width, height, TGAImage::RGB);
	std::vector<std::vector<double>> depth(height, std::vector<double>(width, 1));

	std::string path = "../models/african_head/";
	std::string filename = "african_head";
	mesh obj = ObjLoader::LoadObj(path + filename + ".obj", false);

	GouraudShader shader;
	for (int i = 0; i < obj.vertex_indices.size(); i += 3) {
		Rasterizer::Triangle(obj, i, i + 1, i + 2, shader, framebuffer, depthbuffer, depth);
	}

	depthbuffer.write_tga_file("../_results/Lesson6-african_head_depthbuffer.tga");
	framebuffer.write_tga_file("../_results/Lesson6-african_head_perspective.tga");
}

int main() {
	std::cout << "===== Lesson 6 =====" << std::endl << std::endl;

	render();
}
