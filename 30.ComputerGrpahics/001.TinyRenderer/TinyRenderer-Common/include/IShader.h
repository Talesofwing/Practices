#pragma once

#include "zer0Math.h"
#include "tgaimage.h"
#include "ObjLoader.h"

using namespace zer0;

struct IShader {
	virtual ~IShader();
	virtual vec3 vertex(int nthvert, const vec4& p) = 0;
	virtual bool fragment(double alpha, double beta, double gamma, TGAColor& color) = 0;
};
