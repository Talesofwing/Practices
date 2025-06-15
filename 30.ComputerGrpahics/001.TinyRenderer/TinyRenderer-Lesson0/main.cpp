#include <iostream>

#include "tgaimage.h"

int main(int argc, char** argv) {
	std::cout << "===== Lesson 0 =====" << std::endl << std::endl;

	TGAImage image(100, 100, TGAImage::RGB);
	image.set(52, 41, TGAColor::red);
	image.write_tga_file("../_results/Lesson0.tga");
	return 0;
}
