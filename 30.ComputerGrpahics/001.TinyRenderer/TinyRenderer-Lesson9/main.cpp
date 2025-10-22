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
	vec2 uvs[3];
	vec3 normals[3];

	virtual vec3 vertex(int nthvert, const vec4& p, const vec2& uv, const vec3& n) {
		points[nthvert] = view(eye, up, lookAt) * p;
		uvs[nthvert] = uv;

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

	virtual bool fragment(double alpha, double beta, double gamma, const TGAImage& diff_texture, const TGAImage& spec_texture, const TGAImage& nm, TGAColor& color) {
		vec3 normal = normals[0] * alpha + normals[1] * beta + normals[2] * gamma;
		normal.normalized();

		vec3 p0 = points[0], p1 = points[1], p2 = points[2];
		vec3 e1 = p1 - p0;
		vec3 e2 = p2 - p0;

		vec2 uv0 = uvs[0], uv1 = uvs[1], uv2 = uvs[2];
		double du1 = uv1.x - uv0.x;
		double dv1 = uv1.y - uv0.y;
		double du2 = uv2.x - uv0.x;
		double dv2 = uv2.y - uv0.y;

		double temp = du1 * dv2 - du2 * dv1;

		vec3 t = (e1 * dv2 - e2 * dv1) / temp;
		vec3 b = (e2 * du1 - e1 * du2) / temp;
		vec3 t2 = t - normal * dot(normal, t);
		t2.normalized();
		vec3 b2 = b - normal * dot(normal, b) - t2 * dot(t2, b);
		b2.normalized();

		mat3x3 tbn {
			t2.x, t2.y, t2.z,
			b2.x, b2.y, b2.z,
			normal.x, normal.y, normal.z
		};

		//tbn = mat3x3 {
		//	t2.x, b2.x, n.x,
		//	t2.y, b2.y, n.y,
		//	t2.z, b2.z, n.z
		//};

		vec2 uv = uvs[0] * alpha + uvs[1] * beta + uvs[2] * gamma;

		TGAColor c = nm.get(std::clamp((int)(uv[0] * nm.width()), 0, nm.width() - 1), std::clamp((int)(uv[1] * nm.height()), 0, nm.height() - 1));
		vec3 n = vec3((double)c[2], (double)c[1], (double)c[0]) * 2.0 / 255.0 - vec3(1, 1, 1);
		n = tbn * n;
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

	TGAImage normalmap;
	normalmap.read_tga_file("../models/african_head/african_head_nm_tangent.tga");

	TGAImage diff_texture;
	diff_texture.read_tga_file("../models/african_head/african_head_diffuse.tga");

	TGAImage spec_texture;
	spec_texture.read_tga_file("../models/african_head/african_head_spec.tga");

	std::string path = "../models/african_head/";
	std::string filename = "african_head";
	mesh obj = ObjLoader::LoadObj(path + filename + ".obj", false);

	GouraudShader shader;
	Rasterizer::Triangle_With_Normal_Mapping_And_Texture(obj, shader, framebuffer, depthbuffer, diff_texture, spec_texture, normalmap);

	framebuffer.write_tga_file("../_results/Lesson9/african_head.tga");
}

int main() {
	std::cout << "===== Lesson 9 =====" << std::endl << std::endl;

	render();
}
