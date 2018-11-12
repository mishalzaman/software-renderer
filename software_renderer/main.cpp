#include <SDL.h>
#include <iostream>
#include <string>

#include "Primitive.h"
#include "ObjLoader.h"

#define SDL_MAIN_HANDLED

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
bool quit = false;

ObjLoader* model = new ObjLoader("assets/head.obj");

int main(int argc, char *argv[])
{
	SDL_Event event;
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow(
		"Software Renderer",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0
	);

	// set renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	while (!quit) {
		// Poll shut down
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			quit = true;

		// Clear the previous render buffer
		SDL_RenderClear(renderer);

		// set the colours for the lines
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		// Primitive::line(renderer, 40, 40, 250, 250);
		// Primitive::line(renderer, 250, 250, 250, 40);
		// Primitive::line(renderer, 250, 40, 40, 40);

		int sizeFaces = model->nFaces();
		for (int i = 0; i < model->nFaces(); i++)
		{
			if ((i + 1) >= sizeFaces)
			{
				break;
			}

			Face face = model->face(i);

			Vector3 v1 = model->vertex(face.v1);
			Vector3 v2 = model->vertex(face.v2);
			Vector3 v3 = model->vertex(face.v3);

			int x0 = (v1.x + 1.)*SCREEN_WIDTH / 2.;
			int y0 = (v1.y + 1.)*SCREEN_HEIGHT / 2.;
			int x1 = (v2.x + 1.)*SCREEN_WIDTH / 2.;
			int y1 = (v2.y + 1.)*SCREEN_HEIGHT / 2.;
			int x2 = (v3.x + 1.)*SCREEN_WIDTH / 2.;
			int y2 = (v3.y + 1.)*SCREEN_HEIGHT / 2.;
			Primitive::line(renderer, x0, y0, x1, y1);
			Primitive::line(renderer, x1, y1, x2, y2);
			Primitive::line(renderer, x2, y2, x0, y0);
			// Note: this works but its shitty, need to fix it
		}

		// Set the colour for the background
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderPresent(renderer);
	}

	delete model;
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}