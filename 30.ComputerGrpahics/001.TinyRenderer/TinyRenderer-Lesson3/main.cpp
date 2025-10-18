#include "Rasterizer.h"
#include "ObjLoader.h"
#include "zer0Math.h"

using namespace zer0;

void triangle_depth() {
	constexpr int width = 128;
	constexpr int height = 128;

	TGAImage framebuffer(width, height, TGAImage::RGB);

	Rasterizer::Triangle_With_DepthColor({17, 4, 13}, {55, 39, 128}, {23, 59, 255}, framebuffer);

	framebuffer.write_tga_file("../_results/Lesson3/triangle_depth.tga");
}

void triangle_fullcolored() {
	constexpr int width = 128;
	constexpr int height = 128;

	TGAImage framebuffer(width, height, TGAImage::RGB);

	Rasterizer::Triangle_With_FullColored({17, 4}, {55, 39}, {23, 59}, framebuffer, TGAColor::red, TGAColor::blue, TGAColor::green);

	framebuffer.write_tga_file("../_results/Lesson3/triangle_fullcolored.tga");
}

int main() {
	std::srand(static_cast<unsigned int>(std::time({})));

	std::cout << "===== Lesson 3 =====" << std::endl << std::endl;

	Rasterizer::Culling = true;
	Rasterizer::Wireframe = false;

	triangle_depth();
	triangle_fullcolored();
}
