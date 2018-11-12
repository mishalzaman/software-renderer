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
		// get "v" vertex values
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream v(line.substr(2));
			Vector3 vertex;
			v >> vertex.x;
			v >> vertex.y;
			v >> vertex.z;
			this->vertices.push_back(vertex);
		}

		if (line.substr(0, 3) == "vt ")
		{
			std::istringstream v(line.substr(2));
			Vector3 vertex;
			v >> vertex.x;
			v >> vertex.y;
			v >> vertex.z;
			this->textures.push_back(vertex);
		}

		if (line.substr(0, 3) == "vn ")
		{
			std::istringstream v(line.substr(2));
			Vector3 vertex;
			v >> vertex.x;
			v >> vertex.y;
			v >> vertex.z;
			this->normals.push_back(vertex);
		}

		if (line.substr(0, 2) == "f ")
		{
			std::istringstream v(line.substr(2));
			Vector3i vertex;
			v >> vertex.x;
			v >> vertex.y;
			v >> vertex.z;
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

Vector3 ObjLoader::texture(int index)
{
	return this->textures[index];
}

Vector3i ObjLoader::face(int index)
{
	return this->faces[index];
}

Vector3 ObjLoader::normal(int index)
{
	return this->normals[index];
}

int ObjLoader::nVertices()
{
	return (int)this->vertices.size();
}

int ObjLoader::nTextures()
{
	return (int)this->textures.size();
}

int ObjLoader::nNormals()
{
	return (int)this->normals.size();
}

int ObjLoader::nFaces()
{
	return (int)this->faces.size();
}
