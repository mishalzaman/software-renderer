/*
	Primitive
	Static class to draw primitives:
	- Line
	- Triangle
*/

#include <SDL.h>

class Primitive
{
public:
	// Using BresenHam's line algorithm
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	static void line(SDL_Renderer* renderer, int x0, int y0, int x1, int y1);
private:
	Primitive() {}
};

