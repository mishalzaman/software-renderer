#include "Primitive.h"
#include <iostream>
#include <string>

void Primitive::line(SDL_Renderer* renderer, int x0, int y0, int x1, int y1)
{
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = std::abs(dy) * 2;
	int error2 = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++) {
		if (steep) {
			SDL_RenderDrawPoint(renderer, y, x);
		}
		else {
			SDL_RenderDrawPoint(renderer, x, y);
		}
		error2 += derror2;
		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

void Primitive::triangle(SDL_Renderer* renderer, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	Primitive::line(renderer, v1.x, v1.y, v2.x, v2.y);
	Primitive::line(renderer, v2.x, v2.y, v3.x, v3.y);
	Primitive::line(renderer, v3.x, v3.y, v1.x, v1.y);
}

void Primitive::fillTriangle(SDL_Renderer* renderer, glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	// Primitive::triangle(renderer, a, b, c);
	// std::cout << std::to_string(a.z) << std::endl;

	float minX = a.x < b.x ? (a.x < c.x ? a.x : c.x) : (b.x < c.x ? b.x : c.x);
	float maxX = a.x > b.x ? (a.x > c.x ? a.x : c.x) : (b.x > c.x ? b.x : c.x);
	float minY = a.y < b.y ? (a.y < c.y ? a.y : c.y) : (b.y < c.y ? b.y : c.y);
	float maxY = a.y > b.y ? (a.y > c.y ? a.y : c.y) : (b.y > c.y ? b.y : c.y);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (float y = minY; y <= maxY; y += 1.0)
	{
		for (float x = minX; x <= maxX; x += 1.0)
		{
			glm::vec3 p = { x, y, 1.0 };

			if (Primitive::isBarycentric(p, a, b, c))
			{
				// std::cout << std::to_string(i) << " " << std::to_string(j) << std::endl;
   				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
	}
}

bool Primitive::isBarycentric(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	glm::vec3 v0 = b - a;
	glm::vec3 v1 = c - a;
	glm::vec3 v2 = p - a;
	float d00 = glm::dot(v0, v0);
	float d01 = glm::dot(v0, v1);
	float d11 = glm::dot(v1, v1);
	float d20 = glm::dot(v2, v0);
	float d21 = glm::dot(v2, v1);
	float denom = d00 * d11 - d01 * d01;
	float v = (d11 * d20 - d01 * d21) / denom;
	float w = (d00 * d21 - d01 * d20) / denom;
	float u = 1.0f - v - w;

	// std::cout << std::to_string(v) << " " << std::to_string(u) << " " << std::to_string(w) << std::endl;

	if (v < 0 || u < 0 || w < 0)
	{
		return false;
	}

	return true;
}
