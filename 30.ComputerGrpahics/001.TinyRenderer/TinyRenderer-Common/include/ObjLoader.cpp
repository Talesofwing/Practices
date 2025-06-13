#include "ObjLoader.h"

std::pair<std::vector<Vec3>, std::vector<Face>> ObjLoader::LoadObj(std::string path) {
	Timer timer;
	timer.Start();

	std::vector<Vec3> vertices;
	std::vector<Face> faces;

	std::ifstream ifs(path);
	std::string line;

	// Minimize variable scope for clarity and safety;
	// modern compilers will optimize local variable allocation,
	// so performance impact is negligible.

	// Vec3 v;
	// Face f;

	int c = 0;
	while (std::getline(ifs, line)) {
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "v") {
			double x, y, z;
			iss >> x >> y >> z;
			x = (x + 1) / 2;
			y = (y + 1) / 2;
			z = (z + 1) / 2;
			vertices.emplace_back(x, y, z);
		} else if (prefix == "f") {
			char trash;
			int trash2;
			int v1, v2, v3;
			std::string fStr;
			iss >> v1 >> trash >> trash2 >> trash >> trash2
				>> v2 >> trash >> trash2 >> trash >> trash2
				>> v3;
			v1--;
			v2--;
			v3--;
			faces.emplace_back(v1, v2, v3);
		}
	}

	timer.Stop();

	double elapsed = timer.ElapsedSecond();

	std::filesystem::path p = path;
	std::cout << ".obj file(" << p.filename() << ") Loaded(" << elapsed << " seconds)" << std::endl;
	std::cout << "\tVertex Count: " << vertices.size() << std::endl;
	std::cout << "\tFace Count: " << faces.size() << std::endl;

	return {vertices, faces};
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
	os << "(" << v.X << ", " << v.Y << ", " << v.Z << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Face& f) {
	os << "(" << f.V1 << ", " << f.V2 << ", " << f.V3 << ")";
	return os;
}
