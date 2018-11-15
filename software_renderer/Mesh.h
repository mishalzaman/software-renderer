#pragma once
#include <glm/glm.hpp>
#include <sdl/SDL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


struct Face
{
	int v1, v2, v3;
};

class Mesh
{
public:
	Mesh(const char *filename);
	~Mesh();
	void draw(SDL_Renderer* renderer, int sWidth, int sHeight);
	glm::vec3 vertex(int index);
	Face face(int index);
	int nVertices();
	int nFaces();
private:
	void importObj(const char *filename);
	std::vector<glm::vec3> vertices;
	std::vector<Face> faces;
};

