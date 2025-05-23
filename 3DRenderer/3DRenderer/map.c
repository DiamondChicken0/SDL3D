#include "map.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_iostream.h>

#include <stdio.h>
#include <stdlib.h>

/* Map Conventions
* 
*  The first character of a line denotes its behavior for
*  the upcoming text until it reaches the end behavior character
* 
*  Special Characters
* 
*  # | Comment
*  & | Area Start
*  $ | End Behavior
* 
*  Expected Formats
*  
*  Map Area:
* 
*  # float startX, float startY, float endX, float endY, surfaceMask mask
*  ...
*  $
* 
*  Ex:
*  # 
*  1, 2, 3, 4, SOLID
*  4, 3, 2, 1, NOTSOLID
*  $
*  
*/

bool loadMap(char *name)
{
	SDL_IOStream* file;

	file = SDL_IOFromFile(name, "r");
	if (!file)
	{
		printf("Can't find file of %s\n", name);
		return false;
	}

	char currChar;
	bool newLine = true;
	bool commented = false;
	int currMode = NOTHING;

	while (SDL_ReadIO(file, &currChar, 1))
	{
		printf("Reading %d from %c\n", currChar, currChar);

		if (newLine)
		{
			commented = false;
			switch (currChar)
			{
				case '&':
					currMode = READING_AREA;
					break;
				case '#':
					commented = true;
					break;
				case '$':
					currMode = NOTHING;
					break;
				default:
					break;
			}
			newLine = false;
		}
	}
}