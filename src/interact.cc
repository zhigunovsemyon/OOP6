#include "interact.h"

void InteractMove::click(SDL_Point const &) {}

void InteractDelete::click(SDL_Point const &) {}

void InteractResize::click(SDL_Point const &) {}

#include "circle.h"
void InteractCreate::click(SDL_Point const &point) 
{
	new Circle{point.x, point.y};
}
