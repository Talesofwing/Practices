#pragma once

#include <vector>

#include "zer0Math.h"

using namespace zer0;
 
struct mesh {
	std::vector<vec3> vertices;
	std::vector<vec2> uvs;
	std::vector<vec3> normals;
	std::vector<unsigned int> vertex_indices;
	std::vector<unsigned int> uv_indcies;
	std::vector<unsigned int> normals_indices;
};

std::ostream& operator<<(std::ostream& os, const mesh& m);
