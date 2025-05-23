#include "main.h"
#include "render.h"

void drawInterpolatedLine(pixelAtPoint a, pixelAtPoint b)
{
	float slope = (a.pos[1] - b.pos[1]) / (a.pos[0] - b.pos[0]);
	//printf("%f", slope);
	// Long Lines
	if (abs(slope) <= 1)
	{
		if (slope >= 0)
		{
			for (int i = a.pos[0]; i < b.pos[0]; i++)
			{
				pixels[i][(int)round(slope * i)] = a.pixel;
					
			}
		}
	}
	// Short Lines
	else
	{

	}

}

void drawPolygon(Polygon poly)
{

}