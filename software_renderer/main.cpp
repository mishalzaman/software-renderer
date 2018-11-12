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

	for (int i=0; i < model->nFaces(); i++)
	{
		Vector3i f = model->face(i);
		std::cout << std::to_string(f.x) << std::endl;
	}

	while (!quit) {
		// Poll shut down
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			quit = true;

		// Clear the previous render buffer
		SDL_RenderClear(renderer);
		
		// set the colours for the lines
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		Primitive::line(renderer, 40, 40, 250, 250);
		Primitive::line(renderer, 250, 250, 250, 40);
		Primitive::line(renderer, 250, 40, 40, 40);

		// Set the colour for the background
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderPresent(renderer);
	}

	delete model;
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}