#pragma once
#include "message.h"
#include "obj.h"
#include <SDL2/SDL_rect.h>

class GraphicObject : private SDL_Point, public Object {
private:

protected:
	GraphicObject(int pos_x, int pos_y) : SDL_Point{pos_x, pos_y}
	{
		send_msg(Message{this, Message::Type::OBJ_SPAWN});
	}

	~GraphicObject()
	{
		send_msg(Message{this, Message::Type::OBJ_DEL});
	}

	virtual void draw() const = 0;
};
