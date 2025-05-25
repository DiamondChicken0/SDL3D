#include "math.h"

SDL_Color ScalarMultPixel(SDL_Color a, float scale)
{
	return (SDL_Color) { a.r * scale, a.g* scale, a.b* scale, a.r* scale };
}

SDL_Color PixelAdd(SDL_Color a, SDL_Color b)
{
	return (SDL_Color) { a.r + b.r, a.g + b.g, a.b + b.b, a.r + b.r };
}