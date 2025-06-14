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
#include "Geometry.h"

using namespace zer0;

class ObjLoader {
	ObjLoader() = delete;
	ObjLoader(const ObjLoader&) = delete;

	ObjLoader& operator=(const ObjLoader&) = delete;

public:
	static mesh LoadObj(std::string path);
};
