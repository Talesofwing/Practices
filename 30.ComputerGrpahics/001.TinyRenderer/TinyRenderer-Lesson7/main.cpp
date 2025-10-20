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

	virtual vec3 vertex(int nthvert, const vec4& p) {
		points[nthvert] = p;

		return transform(p, eye, up, lookAt, width, height);
	}

	virtual bool fragment(double alpha, double beta, double gamma, TGAColor& color) {
		vec3 n = cross(points[1] - points[0], points[2] - points[0]);
		n.normalized();
		vec3 r = (n * dot(light_dir, n) * 2 - light_dir);

		double ambient = .3;
		double diff = std::max(0.0, dot(n, light_dir));
		double spec = std::pow(std::max(r.z, 0.0), 35);

		color[0] = std::min(1.0, ambient + 0.4 * diff + 0.9 * spec) * 255;
		color[1] = std::min(1.0, ambient + 0.4 * diff + 0.9 * spec) * 255;
		color[2] = std::min(1.0, ambient + 0.4 * diff + 0.9 * spec) * 255;

		return false;
	}
};

void previous() {

}

void render() {
	light_dir.normalize();

	TGAImage framebuffer(width, height, TGAImage::RGB);
	std::vector<double> depthbuffer(width * height, std::numeric_limits<double>::lowest());

	std::string path = "../models/african_head/";
	std::string filename = "african_head";
	mesh obj = ObjLoader::LoadObj(path + filename + ".obj", false);

	GouraudShader shader;
	Rasterizer::Triangle(obj, shader, framebuffer, depthbuffer);

	framebuffer.write_tga_file("../_results/Lesson7/african_head_perspective.tga");
}

int main() {
	std::cout << "===== Lesson 7 =====" << std::endl << std::endl;

	previous();
	render();
}
