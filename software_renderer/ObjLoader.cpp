#include "ObjLoader.h"



ObjLoader::ObjLoader(const char *filename)
{
	std::ifstream file(filename, std::ios::in);
	if (!file)
	{
		std::cerr << "ERROR::Cannot open " << filename << std::endl;
		exit(1);

	}

	std::string line;

	while (std::getline(file, line))
	{
		char trash;
		// get "v" vertex values
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream v(line.substr(2));
			Vector3 vertex;
			v >> vertex.x;
			v >> vertex.y;
			v >> vertex.z;
			std::cout << std::to_string(vertex.x) << std::endl;
			this->vertices.push_back(vertex);
		}

		if (line.substr(0, 2) == "f ")
		{
			std::istringstream iss(line.substr(2));
			Face vertex;

			int vidx, itrash;
			std::vector<int> f;

			// line format
			// idx/vt/vn
			while (iss >> vidx >> trash >> itrash >> trash >> itrash) {
				vidx--; // in wavefront obj all indices start at 1, not zero
				f.push_back(vidx);
			}
			vertex.v1 = f[0];
			vertex.v2 = f[1];
			vertex.v3 = f[2];
			this->faces.push_back(vertex);
		}
	}
}


ObjLoader::~ObjLoader()
{
}

Vector3 ObjLoader::vertex(int index)
{
	return this->vertices[index];
}

Face ObjLoader::face(int index)
{
	return this->faces[index];
}

int ObjLoader::nVertices()
{
	return (int)this->vertices.size();
}

int ObjLoader::nFaces()
{
	return (int)this->faces.size();
}
