#pragma once

#include "main.h"

#define HEIGHT 400
#define WIDTH 400

typedef float pos3D[3];
typedef float pos2D[2];

typedef struct {
	SDL_Color pixel;
	pos2D pos;
} pixelAtPoint;

typedef struct {
	struct node3D* next;
	pixelAtPoint point;
} node3D;

typedef struct {
	pixelAtPoint* val;
	Polygon* next;
} Polygon;

typedef struct {
	char name[128];
	struct node3D* points;
} map_type;

typedef enum {
	READING_AREA,
	COMMENTED,
	NOTHING
};

extern SDL_Color pixels[WIDTH][HEIGHT];
