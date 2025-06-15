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
	/// <summary>
	/// Load .obj file
	/// </summary>
	/// <param name="path">The file path</param>
	/// <param name="fit">Should [-1, 1] be coonverted to [0, 1]</param>
	/// <returns>.obj file mesh</returns>
	static mesh LoadObj(std::string path, bool fit = true);
};
