#include <SDL2/SDL.h>

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window * Win;
	Win = SDL_CreateWindow("Sample text", 0, 0, 100, 100,
			       SDL_WINDOW_RESIZABLE);

	SDL_Delay(1000 * 3);
	SDL_DestroyWindow(Win);

	SDL_Quit();
}
