#pragma once

#include "zer0Math.h"
#include "tgaimage.h"
#include "ObjLoader.h"

using namespace zer0;

struct IShader {
	virtual ~IShader();
	virtual vec4 vertex(int nthvert, const mesh& model, int vert_index) = 0;
	virtual bool fragment(double alpha, double beta, double gamma, TGAColor& color) = 0;
};
