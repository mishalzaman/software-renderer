#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Vector3
{
	double x, y, z;
};

struct Vector3i
{
	int x, y, z;
};

class ObjLoader
{
public:
	ObjLoader(const char *filename);
	~ObjLoader();
	Vector3 vertex(int index);
	Vector3i face(int index);
	Vector3 texture(int index);
	Vector3 normal(int index);
	int nVertices();
	int nFaces();
	int nTextures();
	int nNormals();
private:
	std::vector<Vector3> vertices;
	std::vector<Vector3i> faces;
	std::vector<Vector3> textures;
	std::vector<Vector3> normals;
};

