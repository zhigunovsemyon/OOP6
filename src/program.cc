#include <algorithm>
#include <cassert>
#include <memory>
#include <stdexcept>

#include "graphic_obj.h"
#include "message.h"
#include "program.h"
#include "sdlexcept.h"

#include <SDL.h>
#ifndef SDL_h_
#include <SDL2/SDL.h>
#endif // !SDL_h_

#include <SDL_render.h>
#ifndef SDL_render_h_
#include <SDL2/SDL_render.h>
#endif // !SDL_render_h_

#include <SDL_surface.h>
#ifndef SDL_surface_h_
#include <SDL2/SDL_surface.h>
#endif // !SDL_surface_h_

/*Функция отрабатывает нажатия пользователя */
void Program::input_handle_()
{
	switch (event_.type) {
	default:
		break;
	case SDL_WINDOWEVENT:
		if (SDL_WINDOWEVENT_CLOSE == event_.window.event)
			send_msg(new MessageExit);
		break;
	case SDL_KEYUP:
		if (event_.key.keysym.scancode == SDL_SCANCODE_TAB)
			send_msg(new MessageBuilderNext);

		if (event_.key.keysym.scancode == SDL_SCANCODE_Q)
			send_msg(new MessageExit);
		send_msg(new MessageKeyboard(event_.key.keysym.scancode));
		break;

	case SDL_MOUSEWHEEL:
		// assert(event_.wheel.y != 0);
		(event_.wheel.y > 0) ? send_msg(new MessageBuilderNext)
				     : send_msg(new MessageBuilderPrev);
		break;
	case SDL_MOUSEBUTTONUP:
		if (event_.button.button == SDL_BUTTON_RIGHT)
			send_msg(new MessageRClick{event_.button.x,
						   event_.button.y});
		if (event_.button.button == SDL_BUTTON_LEFT)
			send_msg(new MessageLClick{event_.button.x,
						   event_.button.y});
		break;
	}
}

/*Функция рисования фона рисовальщика rend, цветом r g b*/
static int DrawBackground_(SDL_Renderer * rend, SDL_Colour const * col)
{
	if (SDL_SetRenderDrawColor(rend, col->r, col->g, col->b, col->a) ||
	    SDL_RenderClear(rend)) {
		return 1;
	}
	/*else*/
	return 0;
}

void Program::msg_handle_()
{
	if (msg_list_.empty())
		return;

	/*Извлечение крайнего сообщения*/
	if (msg_list_.front() == nullptr) {
		msg_list_.pop();
		throw std::runtime_error{"nullptr message"};
	}
	auto & lastmsg = *msg_list_.front();
	msg_list_.pop();

	/*Рассылка сообщения по объектам*/
	auto obj_handle_msg = [&lastmsg](auto * o) {
		o->recieve_msg(&lastmsg);
	};
	std::ranges::for_each(obj_list_, obj_handle_msg);

	switch (lastmsg.code()) {
	case Message::Type::FACT_NEXT:
		facc.next();
		break;
	case Message::Type::FACT_PREV:
		facc.prev();
		break;
	case Message::Type::DELME: {
		auto * o = dynamic_cast<MessageDelete &>(lastmsg).sender();
		obj_list_.remove(&dynamic_cast<GraphicObject &>(*o));
		delete o;
		break;
	}
	/*Если ни один из объектов не перехватил нажатие раннее:*/
	case Message::Type::LCLICK: {
		auto const & click_msg{dynamic_cast<MessageLClick &>(lastmsg)};
		facc.create(click_msg.x(), click_msg.y());
		break;
	}
	case Message::Type::PROG_EXIT:
		runs_ = false;
		break;
	case Message::Type::ADDME: {
		auto const & spawnmsg{dynamic_cast<MessageSpawn &>(lastmsg)};
		auto newobj = dynamic_cast<GraphicObject *>(spawnmsg.sender());
		obj_list_.push_front(newobj);
		break;
	}
	default:
		break;
	}

	delete &lastmsg;
}

/*Диспетчер программы*/
Program & Program::run()
{
	while (runs_) {
		/*Создание сообщений из событий ввода*/
		while (SDL_PollEvent(&event_))
			input_handle_();

		// Обработка событий объектами и программой
		msg_handle_();

		// Заливка фона, завершение работы если не удалось
		if (DrawBackground_(rend_, &bgcolour_))
			throw SDL_exception{};

		/*Отрисовка каждого объекта*/
		auto rend_link = rend_;
		auto draw = [&rend_link](auto const * o) {
			o->draw(rend_link);
		};
		std::ranges::for_each(obj_list_, draw );

		// Вывод на экран
		SDL_RenderPresent(rend_);
	}
	return *this;
}

/*Завершение работы программы*/
Program::~Program()
{
	std::ranges::for_each(builders_, [](auto * p) { delete p; });

	std::ranges::for_each(obj_list_, [](auto * p) { delete p; });

	/*Очистка остальной очереди сообщений*/
	while (!msg_list_.empty()) {
		auto * top = msg_list_.front();
		delete top;
		msg_list_.pop();
	}

	if (rend_)
		SDL_DestroyRenderer(rend_);

	if (win_)
		SDL_DestroyWindow(win_);

	SDL_Quit();
}

/*Запуск программы*/
Program::Program()
{
	/*При неудаче очистка осуществляется сразу в конструкторе,
	т.к. объект не будет создан и не будет вызвано деструктора*/

	/*Запуск SDL*/
	if (SDL_Init(SDL_INIT_VIDEO))
		throw SDL_exception{};

	win_ = SDL_CreateWindow(WinName_.data(), SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, winsize_.x, winsize_.y,
				SDL_WINDOW_SHOWN);
	if (win_ == nullptr) {
		/*Сохранение строки для передачи в исключение.*/
		auto str = SDL_GetError();
		SDL_Quit();
		throw SDL_exception{str};
	}

	rend_ = SDL_CreateRenderer(
		win_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (nullptr == rend_) {
		/*Сохранение строки для передачи в исключение.*/
		auto str = SDL_GetError();
		SDL_DestroyWindow(win_);
		SDL_Quit();
		throw SDL_exception{str};
	}
}

/*Геттер/конструктор объекта программы. Выкидывает исключение при неудачном
 * создании инстанса*/
Program & Program::get()
{
	/*Создаётся при первом вызове. Живёт всю программу*/
	static Program inst_;
	return inst_;
}
