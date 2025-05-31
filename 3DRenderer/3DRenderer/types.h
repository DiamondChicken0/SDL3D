#pragma once

#include "main.h"

#define HEIGHT 400
#define WIDTH 400

typedef float pos3D[3];
typedef float pos2D[2];

typedef struct { 
	float x;
	float y;
	float z;
} vec3;

typedef struct {
	vec3 vertices[3];
} triangle;

typedef struct {
	SDL_Color pixel;
	pos2D pos;
} pixelAtPoint;

typedef struct {
	struct node3D* next;
	pixelAtPoint point;
} node3D;

typedef struct Polygon {
	pixelAtPoint* val;
	struct Polygon* next;
} Polygon;

typedef struct {
	char name[128];
	struct node3D* points;
} map_type;

typedef struct {
	int rows;
	int columns;
	float* data;
} matrix;

typedef enum {
	READING_AREA,
	COMMENTED,
	NOTHING
};

extern SDL_Color pixels[WIDTH][HEIGHT];
