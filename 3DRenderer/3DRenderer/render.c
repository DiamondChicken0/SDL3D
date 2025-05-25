#include "main.h"
#include "render.h"


void drawInterpolatedLine(pixelAtPoint a, pixelAtPoint b)
{
	float slope = (a.pos[1] - b.pos[1]) / (a.pos[0] - b.pos[0]);
	int startX;
	int startY;
	int endX;
	int endY;
	SDL_Color startColor;
	SDL_Color endColor;
	
	if (abs(slope) <= 1)
	{
		if (a.pos[0] <= b.pos[0])
		{
			startX = a.pos[0];
			endX = b.pos[0];
			startColor = a.pixel;
			endColor = b.pixel;
		}
		else
		{
			startX = b.pos[0];
			endX = a.pos[0];
			startColor = b.pixel;
			endColor = a.pixel;
		}
		int length = endX - startX;
		for (int i = startX; i <= endX; i++)
		{
			SDL_Color finalPixel = PixelAdd(
				ScalarMultPixel(startColor, (float) (endX - i)/length),
				ScalarMultPixel(endColor, (float)(i - startX) / length));
			printf("Considering %f of pixel A and %f of pixel B\n", (float)(startX - i) / length, (float)(i - startX) / length);
			pixels[i][(int)round(slope * i)] = finalPixel;
		}
	}
	else
	{
		if (a.pos[1] <= b.pos[1])
		{
			startY = a.pos[1];
			endY = b.pos[1];
			startColor = a.pixel;
			endColor = b.pixel;
		}
		else
		{
			startY = b.pos[1];
			endY = a.pos[1];
			startColor = b.pixel;
			endColor = a.pixel;
		}

		int length = endY - startY;
		for (int i = startY; i <= endY; i++)
		{
			SDL_Color finalPixel = PixelAdd(
				ScalarMultPixel(startColor, (float) (endY - i)/length),
				ScalarMultPixel(endColor, (float)(i - startY) / length));
			printf("Considering %f of pixel A and %f of pixel B\n", (float)(startY - i) / length, (float)(i - startY) / length);
			pixels[(int)round(slope * i)][i] = finalPixel;
		}

	}

}

void drawPolygon(Polygon poly)
{

}