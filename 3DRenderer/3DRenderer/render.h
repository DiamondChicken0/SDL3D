#pragma once

#include "main.h"

#ifndef RENDER_H
#define RENDER_H

SDL_Color pixelBuffer[WIDTH][HEIGHT];

void drawInterpolatedLine(pixelAtPoint *a, pixelAtPoint *b);
void drawUnfilledPolygon(struct Polygon *poly);
void drawFilledPolygon(struct Polygon* poly);
void drawBufferToScreen();
void clearPixelBuffer();

#endif RENDER_H
