#pragma once
#include "obj.h"
#include <SDL2/SDL_rect.h>

class GraphicObject : private SDL_Point, public Object {
private:

protected:
	GraphicObject(int pos_x, int pos_y) : SDL_Point { pos_x, pos_y } {}

	virtual void draw() const = 0;
};
