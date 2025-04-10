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

#include <list>
#include <string_view>

class Program {
private:
	static constexpr SDL_Colour bgcolour_{0x70, 0x70, 0x70, 0xFF};
	static constexpr SDL_Point winsize_{640, 480};
	static constexpr int frametime_{10};
	static constexpr std::string_view WinName_{"Лабораторная работа №6"};

	SDL_Window * win_{};
	SDL_Renderer * rend_{};
	SDL_Event event_{};
	static Program * inst_;

	std::list<Message> msg_list_{};
	std::list<GraphicObject *> obj_list_{};

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
	void run();

	void operator()() { run(); }

	/*Метод получения сообщения из объектов для рассылки другим объектам*/
	void send_msg(Message && msg) { msg_list_.push_back(std::move(msg)); }

	/*Геттер/конструктор объекта программы*/
	static Program * get();

	static void quit()
	{
		delete inst_;
		inst_ = nullptr;
	}
};
