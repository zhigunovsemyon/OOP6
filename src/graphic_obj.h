#pragma once
#include "message.h"
#include "obj.h"

#include <SDL_rect.h>
#ifndef SDL_rect_h_
#include <SDL2/SDL_rect.h>
#endif /* ifndef _SDL_h */

#include <SDL_render.h>
#ifndef SDL_render_h_
#include <SDL2/SDL_render.h>
#endif /* ifndef _SDL_h */

class GraphicObject : public Object {
private:

protected:
	/*Стандартный цвет объекта*/
	static constexpr SDL_Colour def_colour{0xFF, 0, 0, 0xFF};
	/*Цвет выделенного объекта*/
	static constexpr SDL_Colour sel_colour{0, 0xFF, 0, 0xFF};

	/*Координаты центра объекта*/
	SDL_Point pos_;

	/*Флаг выделенности объекта*/
	bool selected_;

	GraphicObject(int pos_x, int pos_y)
		: pos_{pos_x, pos_y}, selected_{false}
	{
		send_msg(new MessageSpawn{this});
	}

	virtual bool covers_(SDL_Point const &) const = 0;

public:
	virtual void draw(SDL_Renderer *) const = 0;

};
