#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <forward_list>
#include <memory>
#include <queue>
#include <string_view>
#include <utility>

#include "graphic_obj.h"
#include "message.h"
#include "obj.h"
#include "sdlexcept.h"

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
#include "square.h"
#include "triangle.h"

struct SDL_InitedProgram {
	SDL_InitedProgram();

	~SDL_InitedProgram();

	SDL_InitedProgram(SDL_InitedProgram const &) = delete;
	SDL_InitedProgram(SDL_InitedProgram &&) = delete;
	auto operator=(SDL_InitedProgram const &)
		-> SDL_InitedProgram & = delete;
	auto operator=(SDL_InitedProgram &&) -> SDL_InitedProgram & = delete;
};

struct SDL_WindowDeleter {
	void operator()(SDL_Window * ptr) const noexcept
	{
		SDL_DestroyWindow(ptr);
	}
};

struct SDL_RendererDeleter {
	void operator()(SDL_Renderer * ptr) const noexcept
	{
		SDL_DestroyRenderer(ptr);
	}
};

class Program : SDL_InitedProgram {
private:
	static constexpr SDL_Colour bgcolour_{0x70, 0x70, 0x70, 0xFF};
	static constexpr SDL_Point winsize_{960, 600};
	static constexpr std::string_view WinName_{"Лабораторная работа №6"};

	CircleBuilder b1{};
	SquareBuilder b2{};
	RectangleBuilder b3{};
	TriangleBuilder b4{};
	std::array<GraphicBuilder *, 4> builders_{&b1, &b2, &b3, &b4};
	GraphicFactory facc{builders_};

	std::unique_ptr<SDL_Window, SDL_WindowDeleter> win_{};
	std::unique_ptr<SDL_Renderer, SDL_RendererDeleter> rend_{};
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
