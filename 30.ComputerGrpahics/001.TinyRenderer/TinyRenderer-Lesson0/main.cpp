#include <iostream>

#include "tgaimage.h"

int main(int argc, char** argv) {
	std::cout << "===== Lesson 0 =====" << std::endl;

	std::cout << "Start rendering..." << std::endl;

	TGAImage image(64, 64, TGAImage::RGB);
	int ax = 7, ay = 3;
	int bx = 12, by = 37;
	int cx = 62, cy = 53;
	image.set(ax, ay, TGAColor::white);
	image.set(bx, by, TGAColor::white);
	image.set(cx, cy, TGAColor::white);
	image.write_tga_file("../_results/Lesson0/image.tga");

	std::cout << "Finish rendering..." << std::endl;

	return 0;
}
