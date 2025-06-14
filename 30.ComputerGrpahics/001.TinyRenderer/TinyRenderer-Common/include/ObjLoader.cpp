#include "ObjLoader.h"

mesh ObjLoader::LoadObj(std::string path) {
	Timer timer;
	timer.Start();

	mesh m;

	std::ifstream ifs(path);
	std::string line;

	// Minimize variable scope for clarity and safety;
	// modern compilers will optimize local variable allocation,
	// so performance impact is negligible.

	// vec3 v;
	// Face f;

	int c = 0;
	while (std::getline(ifs, line)) {
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "v") {
			// vertices

			double x, y, z;
			iss >> x >> y >> z;
			x = (x + 1) / 2;
			y = (y + 1) / 2;
			z = (z + 1) / 2;
			m.vertices.emplace_back(x, y, z);
		} else if (prefix == "f") {
			// indices

			char trash;
			int v1, v2, v3;
			int uv1, uv2, uv3;
			int n1, n2, n3;
			std::string fStr;
			iss >> v1 >> trash >> uv1 >> trash >> n1
				>> v2 >> trash >> uv2 >> trash >> n2
				>> v3 >> trash >> uv3 >> trash >> n3;
			v1--; v2--; v3--;
			uv1--; uv2--; uv3--;
			n1--; n2--; n3--;
			m.vertex_indices.emplace_back(v1);
			m.vertex_indices.emplace_back(v2);
			m.vertex_indices.emplace_back(v3);
			m.uv_indcies.emplace_back(uv1);
			m.uv_indcies.emplace_back(uv2);
			m.uv_indcies.emplace_back(uv3);
			m.normals_indices.emplace_back(n1);
			m.normals_indices.emplace_back(n2);
			m.normals_indices.emplace_back(n3);
		} else if (prefix == "vt") {
			// uv

			double u, v, w;
			iss >> u >> v >> w;

			m.uvs.emplace_back(u, 1.0 - v);
		}
	}

	timer.Stop();

	double elapsed = timer.ElapsedSecond();

	std::filesystem::path p = path;
	std::cout << ".obj file(" << p.filename() << ") Loaded(" << elapsed << " seconds)" << std::endl;
	std::cout << "\tVertex Count: " << m.vertices.size() << std::endl;
	std::cout << "\tIndex Count: " << m.vertex_indices.size() / 3 << std::endl;
	std::cout << "\tUV Count: " << m.uvs.size() << std::endl;

	return m;
}


