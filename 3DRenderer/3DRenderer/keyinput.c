#include "keyinput.h"

void parseKey(SDL_Event* event)
{
	switch (event->key.key)
	{
		case SDLK_ESCAPE:
			printf("Escape Recieved, Quitting\n");
			SDL_Event quitState;
			quitState.type = SDL_EVENT_QUIT;
			SDL_PushEvent(&quitState);
	}
}