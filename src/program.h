#pragma once

#include <algorithm>
#include <array>
#include <forward_list>
#include <queue>
#include <string_view>
#include <utility>

#include "graphic_obj.h"
#include "message.h"
#include "obj.h"

#include <SDL_events.h>
#ifndef SDL_events_h_
#include <SDL2/SDL_events.h>
#endif // !SDL_events_h

#include <SDL_render.h>
#ifndef SDL_render_h_
#include <SDL2/SDL_render.h>
#endif // !SDL_render_h_

#include <SDL_video.h>
#ifndef SDL_video_h_
#include <SDL2/SDL_video.h>
#endif // !SDL_video_h_

#include "circle.h"
#include "graphic_factory.h"
#include "rect.h"
#include "triangle.h"
#include "square.h"

class Program {
private:
	static constexpr SDL_Colour bgcolour_{0x70, 0x70, 0x70, 0xFF};
	static constexpr SDL_Point winsize_{960, 600};
	static constexpr std::string_view WinName_{"Лабораторная работа №6"};

	std::array<GraphicBuilder *, 4> builders_{
		new CircleBuilder, new SquareBuilder, new RectangleBuilder, new TriangleBuilder};
	GraphicFactory facc{builders_};

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
