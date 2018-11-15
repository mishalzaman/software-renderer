#include "Mesh.h"
#include "Primitive.h" // static class

Mesh::Mesh(const char *filename)
{
	this->importObj(filename);
}

Mesh::~Mesh()
{
}

void Mesh::draw(SDL_Renderer* renderer, int sWidth, int sHeight)
{
	int sizeFaces = this->nFaces();
	for (int i = 0; i < this->nFaces(); i++)
	{
		if ((i + 1) >= sizeFaces)
		{
			break;
		}

		Face face = this->face(i);

		glm::vec3 v1 = this->vertex(face.v1);
		glm::vec3 v2 = this->vertex(face.v2);
		glm::vec3 v3 = this->vertex(face.v3);

		float vMu = 1.0;

		int x0 = (v1.x + vMu)*sWidth / 2.;
		int y0 = (vMu - v1.y)*sHeight / 2.; // Getting the vMu - y here so the rendered image is not upside down
		int x1 = (v2.x + vMu)*sWidth / 2.;
		int y1 = (vMu - v2.y)*sHeight / 2.; // Getting the vMu - y here so the rendered image is not upside down
		int x2 = (v3.x + vMu)*sWidth / 2.;
		int y2 = (vMu - v3.y)*sHeight / 2.; // Getting the vMu - y here so the rendered image is not upside down

		Primitive::fillTriangle(renderer, glm::vec3(x0, y0, v1.z), glm::vec3(x1, y1, v2.z), glm::vec3(x2, y2, v3.z));

		// Note: this works but its shitty, need to fix it
	}
}

void Mesh::importObj(const char *filename)
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
			glm::vec3 vertex;
			v >> vertex.x;
			v >> vertex.y;
			v >> vertex.z;
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

glm::vec3 Mesh::vertex(int index)
{
	return this->vertices[index];
}

Face Mesh::face(int index)
{
	return this->faces[index];
}

int Mesh::nVertices()
{
	return (int)this->vertices.size();
}

int Mesh::nFaces()
{
	return (int)this->faces.size();
}
