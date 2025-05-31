#include "main.h"
#include <SDL3/SDL_main.h>

static SDL_Window* mainWin;
static SDL_Renderer* mainRend;

bool running = true;

SDL_Color pixels[WIDTH][HEIGHT];

int main(int argc, char* argv[])
{
	SDL_SetAppMetadata("3D Awesome Sauce", "Pre-Alpha", "com.simon.3drenderer");
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		printf("Err while initialzing SDL: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	if (!SDL_CreateWindowAndRenderer("3D Awesome Sauce", WIDTH, HEIGHT, SDL_WINDOW_OPENGL, &mainWin, &mainRend))
	{
		printf("Window Crashed on Start :(\n");
		return 2;
	}

	pixelAtPoint firstA = { 
		.pixel = {255, 0, 0, 255 },
		.pos = { 200, 200 }
	};

	pixelAtPoint secondA = {
		.pixel = { 0, 255, 0, 255 },
		.pos = { 250, 300 }
	};

	//drawInterpolatedLine(firstA, secondA);

	pixelAtPoint firstB = {
	.pixel = { 0, 0, 255, 255 },
	.pos = { 150, 300 }
	};

	pixelAtPoint secondB = {
		.pixel = { 0, 0, 255, 255 },
		.pos = { 300, 100 }
	};

	//drawInterpolatedLine(firstB, secondB);

	Polygon testPolyA;
	testPolyA.val = &firstA;
	
	Polygon testPolyB;
	testPolyB.val = &secondA;

	Polygon testPolyC;
	testPolyC.val = &firstB;

	testPolyA.next = &testPolyB;
	testPolyB.next = &testPolyC;
	testPolyC.next = NULL;

	clearPixelBuffer();

	/*pixelAtPoint testA = {
	.pixel = { 0, 0, 255, 255 },
	.pos = { 100, 250 }
	};
	pixelAtPoint testB = {
		.pixel = { 0, 0, 255, 255 },
		.pos = { 100, 300 }
	};*/

	//drawInterpolatedLine(&testA, &testB);
	drawFilledPolygon(&testPolyA);
	drawBufferToScreen();

	
	matrix matrixA = (matrix){
		.data = malloc(16 * sizeof(float)),
		.columns = 4,
		.rows = 4
	};
	for (int i = 0; i < 16; i++)
		matrixA.data[i] = i;
	//printMatrix(&matrixA);

	matrixScalarMult(&matrixA, 2);
	
	printMatrix(&matrixA);

	matrix matrixColA = (matrix){
		.data = malloc(4 * sizeof(float)),
		.columns = 1,
		.rows = 4
	};

	for (int i = 0; i < 4; i++)
		matrixColA.data[i] = i;


	matrix result;
	matrixMultByColVector(&matrixColA, &matrixA, &result);
	printMatrix(&result);


	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			printf("New Event Posted\n");
			switch (event.type)
			{
				case SDL_EVENT_QUIT:
					SDL_DestroyWindow(mainWin);
					SDL_Quit();
					return 0;

				case SDL_EVENT_KEY_DOWN:
					//printf("Key Code: %i was pressed\n", event.key.key);
					parseKey(&event);

				}
		}

		//Blit to Screen

		SDL_RenderClear(mainRend);

		
		for (int i = 0; i < WIDTH; i++)
		{
			for (int j = 0; j < HEIGHT; j++)
			{
				SDL_SetRenderDrawColor(mainRend,
					pixels[i][j].r,
					pixels[i][j].g,
					pixels[i][j].b,
					pixels[i][j].a);
				//printf("%i ", pixels[i][j].r);
				SDL_RenderPoint(mainRend, i, j);
			}
		}
		SDL_RenderPresent(mainRend);
	}
	//SDL_Delay(5000);
	SDL_DestroyWindow(mainWin);
	SDL_Quit();
}