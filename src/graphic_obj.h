#pragma once
#include "message.h"
#include "obj.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

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
		send_msg(Message{this, Message::Type::OBJ_SPAWN});
	}

	~GraphicObject() override
	{
		send_msg(Message{this, Message::Type::OBJ_DEL});
	}

public:
	virtual void draw(SDL_Renderer *) const = 0;

	/*Местоположение объекта*/
	SDL_Point const & pos() { return pos_; }
};
