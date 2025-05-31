#pragma once

#include "main.h"

#define FOV 90
#define ASPECT_RATIO 1.77777777777
#define Z_NEAR 1
#define Z_FAR 500

extern matrix* persProj;

SDL_Color ScalarMultPixel(SDL_Color a, float scale);
SDL_Color PixelAdd(SDL_Color a, SDL_Color b);
void matrixScalarMult(matrix* inp, float scale);
void matrixMultByColVector(matrix* a, matrix* b, matrix* result);
void printMatrix(matrix* inp);
void addVec3(vec3* a, vec3* b, vec3* result);
void subVec3(vec3* a, vec3* b, vec3* result);
void projectPoint(matrix* inp, vec3* result);
float screenXFromNDC(float x);
float screenYFromNDC(float y);
