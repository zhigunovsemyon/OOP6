#pragma once

#include <array>
#include <forward_list>
#include <queue>
#include <string_view>
#include <utility>
#include <algorithm>

#include "graphic_obj.h"
#include "message.h"
#include "obj.h"

#include <SDL_events.h>
#ifndef SDL_events_h_
#include <SDL2/SDL_events.h>
#endif // !SDL_events_h

#include <SDL_ttf.h>
#ifndef SDL_TTF_H_
#include <SDL2/SDL_ttf.h>
#endif // !SDL_TTF_H_
//
#include <SDL_render.h>
#ifndef SDL_render_h_
#include <SDL2/SDL_render.h>
#endif // !SDL_render_h_

#include <SDL_video.h>
#ifndef SDL_video_h_
#include <SDL2/SDL_video.h>
#endif // !SDL_video_h_

#include "circle.h"
#include "square.h"

class Program {
private:
	static constexpr SDL_Colour bgcolour_{0x70, 0x70, 0x70, 0xFF};
	static constexpr SDL_Point winsize_{960, 600};
	static constexpr std::string_view WinName_{"Лабораторная работа №6"};

	static constexpr std::string_view FontPath_{
#ifdef WIN32
		"..\\..\\..\\assets\\font.ttf"
#else
		"assets/font.ttf"
#endif
	};
	static constexpr int FontSize_{16};
	static constexpr SDL_Colour TextCol_{0xFF, 0x00, 0x00, 0xFF};

	class Factory {
		std::array<GraphicBuilder *, 2> b_;
		int i{0};

	public:
		Factory()
			: b_{new CircleBuilder{}, new SquareBuilder{}}
		{
		}

		~Factory()
		{
			std::for_each(b_.begin(), b_.end(),
				      [](auto * b) { delete b; });
		}

		void make(int x, int y) { b_[i]->create(x, y); };

		void prev()
		{
			if (--i < 0)
				i = (int)b_.size() - 1;
		}

		void next()
		{
			if (++i >= (int)b_.size())
				i = 0;
		}
	} facc;

	TTF_Font * font_{};
	SDL_Window * win_{};
	SDL_Renderer * rend_{};
	SDL_Event event_{};

	/*Очередь сообщений*/
	std::queue<Message *> msg_list_{};

	/*Набор рисуемых объектов*/
	std::forward_list<GraphicObject *> obj_list_{};

	Program(); /*Конструктор программы. Выбрасывает исключения*/

	/*Обработка ввода*/
	void input_handle_();

	/*Обработка сообщений*/
	void msg_handle_();

	~Program(); /*Деструктор программы*/

	void draw_text(std::string_view, SDL_Point const & corner);

	bool runs_{true};

public:
	/*Удаление конструктора копирования*/
	Program(Program const &) = delete;

	/*Удаление операции присвоения*/
	Program & operator=(Program const &) = delete;

	/*Диспетчер*/
	Program & run();

	Program & operator()() { return run(); }

	/*Метод получения сообщения из объектов для рассылки другим объектам*/
	void send_msg(Message * msg) { msg_list_.push(msg); }

	/*Геттер/конструктор объекта программы*/
	static Program & get();

	/*Размер окна*/
	static constexpr SDL_Point const & winsize() { return winsize_; };
};
