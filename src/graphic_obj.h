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
	static constexpr int step{7};
	/*Стандартный цвет объекта*/
	static constexpr SDL_Colour def_colour{0xFF, 0, 0, 0xFF};
	/*Цвет выделенного объекта*/
	static constexpr SDL_Colour sel_colour{0, 0xFF, 0, 0xFF};

	/*Текущий цвет*/
	auto  cur_colour() const noexcept {return selected_ ? sel_colour : def_colour;}

	/*Координаты центра объекта*/
	SDL_Point pos_;

	/*Флаг выделенности объекта*/
	bool selected_;

	GraphicObject(int pos_x, int pos_y)
		: pos_{pos_x, pos_y}, selected_{false}
	{
		send_msg(new MessageSpawn{this});
	}

	virtual bool covers_(SDL_Point const &) const noexcept = 0;

	void left_() noexcept;

	void right_() noexcept;

	void down_() noexcept;

	void up_() noexcept;

	virtual void bigger_() noexcept = 0;
	virtual void smaller_() noexcept = 0;
	virtual void taller_() noexcept = 0;
	virtual void wider_() noexcept = 0;
	virtual void narrower_() noexcept = 0;
	virtual void lower_() noexcept = 0;

public:
	virtual void recieve_msg(Message *) override;

	virtual void draw(SDL_Renderer *) const = 0;
};

class GraphicBuilder {
public:
	virtual ~GraphicBuilder() = default;
	virtual GraphicObject * create(int x, int y) const = 0;
};
