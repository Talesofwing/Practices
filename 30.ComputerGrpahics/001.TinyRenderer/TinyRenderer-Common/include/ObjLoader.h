#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <tuple>

#include "Timer.h"
#include "zer0Math.h"

struct Face {
public:
	Face(int v1, int v2, int v3) : V1(v1), V2(v2), V3(v3) {}

public:
	int V1, V2, V3;
};

class ObjLoader {
	ObjLoader() = delete;
	ObjLoader(const ObjLoader&) = delete;

	ObjLoader& operator=(const ObjLoader&) = delete;

public:
	static std::pair<std::vector<zer0::vec3>, std::vector<Face>> LoadObj(std::string path);
};

std::ostream& operator<<(std::ostream& os, const Face& f);
