#include "interact.h"

void InteractMove::click(SDL_Point const &) {}

void InteractDelete::click(SDL_Point const &) {}

void InteractResize::click(SDL_Point const &) {}

#include "circle.h"
void InteractCreate::click(SDL_Point const &point) 
{
	new Circle{point.x, point.y};
}

void InteractMove::kb_press(SDL_Scancode) const {}
void InteractDelete::kb_press(SDL_Scancode) const {}
void InteractCreate::kb_press(SDL_Scancode) const {}
void InteractResize::kb_press(SDL_Scancode) const {}