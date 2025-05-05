#include "program.h"
#include "sdlexcept.h"
#include "ttfexcept.h"
#include "message.h"
#include <cassert>

#include <SDL.h>
#ifndef SDL_h_
#include <SDL2/SDL.h>
#endif // !SDL_h_

#include <SDL_ttf.h>
#ifndef SDL_TTF_H_
#include <SDL2/SDL_ttf.h>
#endif // !SDL_h_

void Program::msg_handle_(bool & runs)
{
	if (msg_list_.empty())
		return;

	/*Извлечение крайнего сообщения*/
	auto & lastmsg = msg_list_.front();

	switch (lastmsg.code()) {
	case Message::Type::PROG_EXIT:
		runs = false;
		break;
	default:
		break;
	}

	msg_list_.pop();
}

/*Функция отрабатывает нажатия пользователя */
void Program::input_handle_()
{
	switch (event_.type) {
	default:
		break;
	case SDL_WINDOWEVENT:
		if (SDL_WINDOWEVENT_CLOSE == event_.window.event)
			send_msg(Message{NULL, Message::Type::PROG_EXIT});
		break;
	case SDL_KEYUP:
		// if (SDL_SCANCODE_E == event_.key.keysym.scancode && (KMOD_ALT
		// & event_.key.keysym.mod))

		if (SDL_SCANCODE_ESCAPE == event_.key.keysym.scancode)
			send_msg(Message{NULL, Message::Type::PROG_EXIT});
		if (SDL_SCANCODE_Q == event_.key.keysym.scancode)
			send_msg(Message{NULL, Message::Type::PROG_EXIT});
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

/*Диспетчер программы*/
Program & Program::run()
{
	bool runs{true};
	while (runs) { // Обработка событий
		while (SDL_PollEvent(&event_))
			input_handle_();

		msg_handle_(runs);

		// Заливка фона, завершение работы если не удалось
		if (DrawBackground_(rend_, &bgcolour_))
			throw SDL_exception{};

		SDL_RenderPresent(rend_); // Вывод его на экран
		SDL_Delay(frametime_); // Задержка перед новым этапом отрисовки
	}

	return *this;
}

/*Завершение работы программы*/
Program::~Program()
{
	if (rend_)
		SDL_DestroyRenderer(rend_);

	if (win_)
		SDL_DestroyWindow(win_);

	TTF_Quit();
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

	/*Запуск SDL_ttf*/
	if (TTF_Init()) {
		SDL_Quit();
		throw TTF_exception{};
	}

	win_ = SDL_CreateWindow(WinName_.data(), SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, winsize_.x, winsize_.y,
				SDL_WINDOW_SHOWN);
	if (win_ == nullptr){
		/*Сохранение строки для передачи в исключение.*/
		auto str = SDL_GetError();
		TTF_Quit();
		SDL_Quit();
		throw SDL_exception{str};
	}

	rend_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED);
	if (nullptr == rend_){
		/*Сохранение строки для передачи в исключение.*/
		auto str = SDL_GetError();
		SDL_DestroyWindow(win_);
		TTF_Quit();
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