/*
	Primitive
	Static class to draw primitives:
	- Line
	- Triangle
*/

#include <sdl/SDL.h>
#include <glm/glm.hpp>

class Primitive
{
public:
	// Using BresenHam's line algorithm
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	static void line(SDL_Renderer* renderer, int x0, int y0, int x1, int y1);
	static void triangle(SDL_Renderer* renderer, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
	static void fillTriangle(SDL_Renderer* renderer, glm::vec3 a, glm::vec3 b, glm::vec3 c);
	static bool isBarycentric(glm::vec3 p, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
private:
	Primitive() {}
};

