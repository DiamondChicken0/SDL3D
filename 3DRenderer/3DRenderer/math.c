#include "math.h"

matrix* persProj = NULL;

SDL_Color ScalarMultPixel(SDL_Color a, float scale)
{
	return (SDL_Color) { a.r * scale, a.g* scale, a.b* scale, a.r* scale };
}

SDL_Color PixelAdd(SDL_Color a, SDL_Color b)
{
	return (SDL_Color) { a.r + b.r, a.g + b.g, a.b + b.b, a.r + b.r };
}

void printMatrix(matrix* inp)
{
	float* data = inp->data;
	for (int i = 0; i < inp->rows; i++)
	{
		for (int j = 0; j < inp->columns; j++)
		{
			printf("%f ", *data);
			data++;
		}
		printf("\n");
	}
}
void matrixScalarMult(matrix* inp, float scale)
{
	for (int i = 0; i < inp->columns * inp->rows; i++)
		inp->data[i] *= scale;
}

void matrixMultByColVector(matrix* a, matrix* b, matrix* result)
{
	matrix colVector;
	matrix sqMatrix;

	if (a->columns == 1)
	{
		colVector = *a;
		sqMatrix = *b;
	}
	else if (b->columns == 1)
	{
		colVector = *b;
		sqMatrix = *a;
	}
	else
	{
		printf("Error: No Column Vector Found\n");
		return;
	}

	if (sqMatrix.rows != colVector.rows)
	{
		printf("Error: Mismatched Sizes of Matrices\n");
		return;
	}

	if (!result->data)
		free(result->data);
	result->columns = 1;
	result->rows = sqMatrix.rows;
	result->data = malloc(sqMatrix.rows * sizeof(float));
	memset(result->data, 0, sqMatrix.rows * sizeof(float));
	for (int i = 0; i < sqMatrix.rows * sqMatrix.columns; i++)
		result->data[i / sqMatrix.columns] += sqMatrix.data[i] * colVector.data[i / sqMatrix.columns];


}

void addVec3(vec3* a, vec3* b, vec3* result)
{
	result->x = a->x + b->x;
	result->y = a->y + b->y;
	result->z = a->z + b->z;
}

void subVec3(vec3* a, vec3* b, vec3* result)
{
	result->x = a->x - b->x;
	result->y = a->y - b->y;
	result->z = a->z - b->z;
}

void projectPoint(matrix* inp, vec3* result)
{
	if (!persProj)
	{
		persProj = malloc(sizeof(matrix));
		*persProj = (matrix) {
		.data = malloc(16 * sizeof(float)),
		.columns = 4, .rows = 4 };

		for (int i = 0; i < 16; i++)
			persProj->data[i] = 0;

		persProj->data[0] = 1 / (ASPECT_RATIO * tanf(FOV / 2));
		persProj->data[5] = 1 / (tanf(FOV / 2));
		persProj->data[10] = (Z_FAR + Z_NEAR) / (Z_NEAR - Z_FAR);
		persProj->data[11] = (2 * Z_FAR * Z_NEAR) / (Z_NEAR - Z_FAR);
		persProj->data[14] = -1;
	}

	matrix outcome;

	matrixMultByColVector(persProj, inp, &outcome);

	result->x = outcome.data[0] / outcome.data[3];
	result->y = outcome.data[1] / outcome.data[3];
	result->z = outcome.data[2] / outcome.data[3];
	
	free(outcome.data);
}

float screenXFromNDC(float x)
{
	(x + 1) / 2 * WIDTH;
}

float screenYFromNDC(float y)
{
	(1 - y) / 2 * HEIGHT;
}