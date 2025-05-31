#include "main.h"
#include "render.h"

SDL_Color pixelBuffer[WIDTH][HEIGHT];

void clearPixelBuffer()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			pixelBuffer[i][j] = (SDL_Color){0, 0, 0, 0};
		}
	}
}

void drawBufferToScreen()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (pixelBuffer[i][j].r != 0 || pixelBuffer[i][j].g != 0 || pixelBuffer[i][j].b != 0)
			{
				pixels[i][j] = pixelBuffer[i][j];
			}
		}
	}
}
void drawInterpolatedLine(pixelAtPoint *a, pixelAtPoint *b)
{
	if (a->pos[1] == b->pos[1] && a->pos[0] == b->pos[0])
		return;
	float slope = (a->pos[1] - b->pos[1]) / (a->pos[0] - b->pos[0]);
	int startX;
	int startY;
	int endX;
	int endY;
	SDL_Color startColor;
	SDL_Color endColor;
	
	// vertical line
	if (isinf(slope))
	{
		if (a->pos[1] <= b->pos[1])
		{
			startY = a->pos[1];
			endY = b->pos[1];
			startColor = a->pixel;
			endColor = b->pixel;
		}
		else
		{
			startY = b->pos[1];
			endY = a->pos[1];
			startColor = b->pixel;
			endColor = a->pixel;
		}
		for (int i = startY; i <= endY; i++)
		{
			pixelBuffer[i][(int)a->pos[0]] = PixelAdd(
				ScalarMultPixel(startColor, (float)(endY - i) / (endY - startY)),
				ScalarMultPixel(endColor, (float)(i - startY) / (endY - startY)));
		}
	}
	// horizontal line
	else if (slope == 0)
	{
		if (a->pos[0] <= b->pos[0])
		{
			startX = a->pos[0];
			endX = b->pos[0];
			startColor = a->pixel;
			endColor = b->pixel;
		}
		else
		{
			startX = b->pos[0];
			endX = a->pos[0];
			startColor = b->pixel;
			endColor = a->pixel;
		}
		for (int i = startX; i <= endX; i++)
		{
			pixelBuffer[i][(int)a->pos[1]] = PixelAdd(
				ScalarMultPixel(startColor, (float)(endX - i) / (endX - startX)),
				ScalarMultPixel(endColor, (float)(i - startX) / (endX - startX)));
		}
	}

	else if (abs(slope) <= 1)
	{
		if (a->pos[0] <= b->pos[0])
		{
			startX = a->pos[0];
			endX = b->pos[0];
			startColor = a->pixel;
			endColor = b->pixel;
		}
		else
		{
			startX = b->pos[0];
			endX = a->pos[0];
			startColor = b->pixel;
			endColor = a->pixel;
		}
		int length = endX - startX;
		for (int i = startX; i <= endX; i++)
		{
			SDL_Color finalPixel = PixelAdd(
				ScalarMultPixel(startColor, (float) (endX - i)/length),
				ScalarMultPixel(endColor, (float)(i - startX) / length));
			//printf("Considering %f of pixel A and %f of pixel B\n", (float)(startX - i) / length, (float)(i - startX) / length);
			int y = round(a->pos[1] + slope * (i - a->pos[0]));
			pixelBuffer[y][i] = finalPixel;
		}
	}
	else
	{
		if (a->pos[1] <= b->pos[1])
		{
			startY = a->pos[1];
			endY = b->pos[1];
			startColor = a->pixel;
			endColor = b->pixel;
		}
		else
		{
			startY = b->pos[1];
			endY = a->pos[1];
			startColor = b->pixel;
			endColor = a->pixel;
		}

		int length = endY - startY;
		for (int i = startY; i <= endY; i++)
		{
			SDL_Color finalPixel = PixelAdd(
				ScalarMultPixel(startColor, 1 - (float)(i - startY) / length),
				ScalarMultPixel(endColor, (float)(i - startY) / length));
			//printf("Considering %f of pixel A and %f of pixel B\n", 1 - (float)(i - startY) / length, (float)(i - startY) / length);
			int x = round(a->pos[0] + (1.0 / slope) * (i - a->pos[1]));
			pixelBuffer[x][i] = finalPixel;

		}

	}
	//printf("Drew a line from (%f, %f) to (%f, %f) with slope of %f\n", a->pos[0], a->pos[1], b->pos[0], b->pos[1], slope);

}

void drawUnfilledPolygon(struct Polygon *poly)
{
	if (!poly || !poly->next)
		return;
	printf("Drawing unfilled polygon\n");

	struct Polygon *polyIter = poly;

	while (polyIter && polyIter->next)
	{
		if (!polyIter->val || !polyIter->next->val)
			return;

		drawInterpolatedLine(polyIter->val, polyIter->next->val);
		polyIter = polyIter->next;

	}
	drawInterpolatedLine(polyIter->val, poly->val);

}

void drawFilledPolygon(struct Polygon *poly)
{
	drawUnfilledPolygon(poly);

	bool insidePoly = false;

	typedef struct pairOfPixels {
		pixelAtPoint a;
		pixelAtPoint b;
		struct pairOfPixels *next;
	} pairOfPixels;

	struct pairOfPixels *start = NULL;
	struct pairOfPixels *nextPair = malloc(sizeof(pairOfPixels));

	for (int j = 0; j < WIDTH; j++)
	{
		insidePoly = false;
		for (int i = 0; i < HEIGHT; i++)
		{
			if (pixelBuffer[i][j].r != 0 || pixelBuffer[i][j].g != 0 || pixelBuffer[i][j].b != 0)
			{
				if (!insidePoly)
				{
					nextPair = malloc(sizeof(pairOfPixels));

					nextPair->a = (pixelAtPoint) {
						.pixel = pixelBuffer[i][j],
						.pos = { i, j }
					};

					insidePoly = !insidePoly;
				}
				else
				{
					nextPair->b = (pixelAtPoint){
						.pixel = pixelBuffer[i][j],
						.pos = { i, j }
					};

					nextPair->next = NULL;
					
					if (!start)
					{
						start = nextPair;
						continue;
					}
					
					pairOfPixels *iter = start;
					
					while (iter && iter->next) 
					{
						iter = iter->next;
					}
					iter->next = nextPair;
					insidePoly = !insidePoly;

					//printf("Created new pair\n");
				}
			}
		}
	}

	pairOfPixels* iter = start;

	while (iter)
	{
		//printf("looping %f, %f thru %f, %f\n", iter->a.pos[0], iter->a.pos[1], iter->b.pos[0], iter->b.pos[1]);
		drawInterpolatedLine(&iter->a, &iter->b);
		iter = iter->next;
	}

}