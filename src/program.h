#pragma once

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
#endif

#include <SDL_video.h>
#ifndef SDL_video_h_
#include <SDL2/SDL_video.h>
#endif // !SDL_video_h_

#include <string_view>
#include <queue>

class Program {
private:
	static constexpr SDL_Colour bgcolour_{0x70, 0x70, 0x70, 0xFF};
	static constexpr SDL_Point winsize_{640, 480};
	static constexpr int frametime_{10};
	static constexpr std::string_view WinName_{"Лабораторная работа №6"};

	SDL_Window * win_{};
	SDL_Renderer * rend_{};
	SDL_Event event_{};

	std::queue<Message> msg_list_{};
	std::queue<GraphicObject *> obj_list_{};

	Program(); /*Конструктор программы. Выбрасывает исключения*/

	/*Обработка ввода*/
	void input_handle_();

	/*Обработка сообщений*/
	void msg_handle_(bool & runs);

	~Program(); /*Деструктор программы*/

public:
	/*Удаление конструктора копирования*/
	Program(Program const &) = delete;

	/*Удаление операции присвоения*/
	Program & operator=(Program const &) = delete;

	/*Диспетчер*/
	Program & run();

	Program & operator()() { return run(); }

	/*Метод получения сообщения из объектов для рассылки другим объектам*/
	void send_msg(Message && msg) { msg_list_.push(std::move(msg)); }

	/*Геттер/конструктор объекта программы*/
	static Program & get();
};
