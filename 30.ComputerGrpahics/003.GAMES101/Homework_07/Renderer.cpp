//
// Created by goksu on 2/25/20.
//

#include <fstream>
#include "Scene.hpp"
#include "Renderer.hpp"

#include <thread>
#include <omp.h>

inline float deg2rad(const float& deg) { return deg * M_PI / 180.0; }

const float EPSILON = 0.00001;

// The main render function. This where we iterate over all pixels in the image,
// generate primary rays and cast these rays into the scene. The content of the
// framebuffer is saved to a file.
void Renderer::Render(const Scene& scene) {
	std::vector<Vector3f> framebuffer(scene.width * scene.height);

	float scale = tan(deg2rad(scene.fov * 0.5));
	float imageAspectRatio = scene.width / (float)scene.height;
	Vector3f eye_pos(278, 273, -800);

	int spp = 128;
	std::cout << "SPP: " << spp << "\n";
	uint32_t hxw = scene.height * scene.width;
	std::atomic<int> process {0};
	int step = hxw / 100;
#pragma omp parallel for
	for (uint32_t p = 0; p < hxw; ++p) {
		int i = p % scene.height;
		int j = p / scene.height;

		float x = (2 * (i + 0.5f) / scene.width - 1) * imageAspectRatio * scale;
		float y = (1 - 2 * (j + 0.5f) / scene.height) * scale;

		Vector3f dir = normalize(Vector3f(-x, y, 1));
		for (int k = 0; k < spp; k++) {
			framebuffer[p] += scene.castRay(Ray(eye_pos, dir), 0) / spp;
		}

		int done = ++process;
		if (done % step == 0 || done == hxw) {
#pragma omp critical
			UpdateProgress(done / (float)hxw);
		}
	}
	UpdateProgress(1.f);

	// save framebuffer to file
	FILE* fp = fopen("binary.ppm", "wb");
	(void)fprintf(fp, "P6\n%d %d\n255\n", scene.width, scene.height);
	for (auto i = 0; i < scene.height * scene.width; ++i) {
		static unsigned char color[3];
		color[0] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].x), 0.6f));
		color[1] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].y), 0.6f));
		color[2] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].z), 0.6f));
		fwrite(color, 1, 3, fp);
	}
	fclose(fp);
}
