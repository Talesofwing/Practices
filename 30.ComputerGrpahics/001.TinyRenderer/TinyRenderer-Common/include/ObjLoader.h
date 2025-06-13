#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <tuple>

#include "Timer.h"

struct Vec3 {
public:
	Vec3() : X(0), Y(0), Z(0) {}
	Vec3(double x, double y, double z) : X(x), Y(y), Z(z) {}

public:
	double X, Y, Z;
};

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
	static std::pair<std::vector<Vec3>, std::vector<Face>> LoadObj(std::string path);
};

std::ostream& operator<<(std::ostream& os, const Vec3& v);
std::ostream& operator<<(std::ostream& os, const Face& f);
