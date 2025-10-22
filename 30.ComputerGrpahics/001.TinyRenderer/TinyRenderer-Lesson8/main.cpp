#include "Rasterizer.h"
#include "ObjLoader.h"
#include "zer0Math.h"
#include "IShader.h"

constexpr int width = 1024;
constexpr int height = 1024;

vec3 eye(-1, 0, 2);
vec3 up(0, 1, 0);
vec3 lookAt(0, 0, 0);

vec3 light_dir(1, 1, 1);

struct GouraudShader : public IShader {
	vec3 points[3];
	vec3 normals[3];
	vec2 uvs[3];

	virtual vec3 vertex(int nthvert, const vec4& p, const vec3& n) {
		points[nthvert] = view(eye, up, lookAt) * p;
		
		// I was too lazy to implement the inverse matrix calculation,
		// so I just hardcoded its inverse transpose matrix.
		mat4x4 inverse_transpose {
			0.8944269, 0, 0.4472139, 0,
			0, 1, 0, 0,
			-0.447213, 0, 0.8944269, 0,
			-1.0000017, 0, 2.0000001, 1
		};
		normals[nthvert] = inverse_transpose * n;

		return transform(p, eye, up, lookAt, width, height);
	}

	virtual bool fragment(double alpha, double beta, double gamma, TGAColor& color) {
		vec3 n = normals[0] * alpha + normals[1] * beta + normals[2] * gamma;
		n.normalized();
		vec3 r = (n * dot(light_dir, n) * 2 - light_dir);
		r.normalized();

		double ambient = .3;
		double diff = std::max(0.0, dot(n, light_dir));
		double spec = std::pow(std::max(r.z, 0.0), 35);

		color[0] = std::min(1.0, ambient + 0.4 * diff + 0.9 * spec) * 255;
		color[1] = std::min(1.0, ambient + 0.4 * diff + 0.9 * spec) * 255;
		color[2] = std::min(1.0, ambient + 0.4 * diff + 0.9 * spec) * 255;

		return false;
	}

	virtual vec3 vertex(int nthvert, const vec4& p, const vec2& uv) {
		points[nthvert] = view(eye, up, lookAt) * p;
		uvs[nthvert] = uv;

		return transform(p, eye, up, lookAt, width, height);
	}

	virtual vec3 vertex(int nthvert, const vec4& p, const vec2& uv, const vec3& n) {
		points[nthvert] = view(eye, up, lookAt) * p;
		uvs[nthvert] = uv;
		normals[nthvert] = n;

		return transform(p, eye, up, lookAt, width, height);
	}

	virtual bool fragment(double alpha, double beta, double gamma, const TGAImage& nm, TGAColor& color) {
		vec2 uv = uvs[0] * alpha + uvs[1] * beta + uvs[2] * gamma;

		TGAColor c = nm.get(std::clamp((int)(uv[0] * nm.width()), 0, nm.width() - 1), std::clamp((int)(uv[1] * nm.height()), 0, nm.height() - 1));
		vec3 n = vec3((double)c[2], (double)c[1], (double)c[0]) * 2.0/255.0 - vec3(1, 1, 1);

		// I was too lazy to implement the inverse matrix calculation,
		// so I just hardcoded its inverse transpose matrix.
		mat4x4 inverse_transpose {
			0.8944269, 0, 0.4472139, 0,
			0, 1, 0, 0,
			-0.447213, 0, 0.8944269, 0,
			-1.0000017, 0, 2.0000001, 1
		};

		n = inverse_transpose * n;
		n.normalized();
		vec3 r = (n * dot(light_dir, n) * 2 - light_dir);
		r.normalized();

		double ambient = .3;
		double diff = std::max(0.0, dot(n, light_dir));
		double spec = std::pow(std::max(r.z, 0.0), 35);

		color[0] = std::min(1.0, ambient + 0.4 * diff + 0.9 * spec) * 255;
		color[1] = std::min(1.0, ambient + 0.4 * diff + 0.9 * spec) * 255;
		color[2] = std::min(1.0, ambient + 0.4 * diff + 0.9 * spec) * 255;

		return false;
	}

	virtual bool fragment(double alpha, double beta, double gamma, const TGAImage& diff_texture, const TGAImage& spec_texture, const TGAImage& nm, TGAColor& color) {
		vec2 uv = uvs[0] * alpha + uvs[1] * beta + uvs[2] * gamma;

		TGAColor c = nm.get(std::clamp((int)(uv[0] * nm.width()), 0, nm.width() - 1), std::clamp((int)(uv[1] * nm.height()), 0, nm.height() - 1));
		vec3 n = vec3((double)c[2], (double)c[1], (double)c[0]) * 2.0 / 255.0 - vec3(1, 1, 1);

		// I was too lazy to implement the inverse matrix calculation,
		// so I just hardcoded its inverse transpose matrix.
		mat4x4 inverse_transpose {
			0.8944269, 0, 0.4472139, 0,
			0, 1, 0, 0,
			-0.447213, 0, 0.8944269, 0,
			-1.0000017, 0, 2.0000001, 1
		};

		n = inverse_transpose * n;
		n.normalized();
		vec3 r = (n * dot(light_dir, n) * 2 - light_dir);
		r.normalized();

		double ambient = .3;
		double diff = std::max(0.0, dot(n, light_dir));
		double spec = std::pow(std::max(r.z, 0.0), 35);

		TGAColor diffColor = diff_texture.get(uv[0] * diff_texture.width(), uv[1] * diff_texture.height());
		TGAColor specColor = spec_texture.get(uv[0] * spec_texture.width(), uv[1] * spec_texture.height());
		specColor[1] = specColor[0];
		specColor[2] = specColor[0];

		color[0] = std::min(255.0, ambient + diffColor[0] * diff + specColor[0] * spec);
		color[1] = std::min(255.0, ambient + diffColor[1] * diff + specColor[1] * spec);
		color[2] = std::min(255.0, ambient + diffColor[2] * diff + specColor[2] * spec);

		return false;
	}
};

void render() {
	light_dir.normalize();

	TGAImage framebuffer(width, height, TGAImage::RGB);
	std::vector<double> depthbuffer(width * height, std::numeric_limits<double>::lowest());

	std::string path = "../models/african_head/";
	std::string filename = "african_head";
	mesh obj = ObjLoader::LoadObj(path + filename + ".obj", false);

	GouraudShader shader;
	Rasterizer::Triangle_With_Smooth_Normal(obj, shader, framebuffer, depthbuffer);

	framebuffer.write_tga_file("../_results/Lesson8/african_head.tga");
}

void render_normal_mapping() {
	light_dir.normalize();

	TGAImage framebuffer(width, height, TGAImage::RGB);
	std::vector<double> depthbuffer(width * height, std::numeric_limits<double>::lowest());

	TGAImage normalmap;
	normalmap.read_tga_file("../models/african_head/african_head_nm.tga");

	std::string path = "../models/african_head/";
	std::string filename = "african_head";
	mesh obj = ObjLoader::LoadObj(path + filename + ".obj", false);

	GouraudShader shader;
	Rasterizer::Triangle_With_Normal_Mapping(obj, shader, framebuffer, depthbuffer, normalmap);

	framebuffer.write_tga_file("../_results/Lesson8/african_head_normal_mapping.tga");
}

void render_normal_mapping_texture() {
	light_dir.normalize();

	TGAImage framebuffer(width, height, TGAImage::RGB);
	std::vector<double> depthbuffer(width * height, std::numeric_limits<double>::lowest());

	TGAImage normalmap;
	normalmap.read_tga_file("../models/african_head/african_head_nm.tga");

	TGAImage diff_texture;
	diff_texture.read_tga_file("../models/african_head/african_head_diffuse.tga");

	TGAImage spec_texture;
	spec_texture.read_tga_file("../models/african_head/african_head_spec.tga");

	std::string path = "../models/african_head/";
	std::string filename = "african_head";
	mesh obj = ObjLoader::LoadObj(path + filename + ".obj", false);

	GouraudShader shader;
	Rasterizer::Triangle_With_Normal_Mapping_And_Texture(obj, shader, framebuffer, depthbuffer, diff_texture, spec_texture, normalmap);

	framebuffer.write_tga_file("../_results/Lesson8/african_head_normal_mapping_texture.tga");
}

int main() {
	std::cout << "===== Lesson 8 =====" << std::endl << std::endl;

	render();
	render_normal_mapping();
	render_normal_mapping_texture();
}
