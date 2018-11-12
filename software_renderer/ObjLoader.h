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

struct Face
{
	int v1, v2, v3;
};

class ObjLoader
{
public:
	ObjLoader(const char *filename);
	~ObjLoader();
	Vector3 vertex(int index);
	Face face(int index);
	int nVertices();
	int nFaces();
private:
	std::vector<Vector3> vertices;
	std::vector<Face> faces;
};

