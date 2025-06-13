#include "tgaimage.h"

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	image.set(52, 41, TGAColor::red);
	image.write_tga_file("../_results/Lesson0.tga");
	return 0;
}
