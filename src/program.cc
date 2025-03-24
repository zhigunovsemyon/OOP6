#include "program.h"
#include "message.h"
#include <cassert>

void Program::msg_handle_(bool & runs)
{
	if (msg_list_.empty())
		return;

	/*Извлечение крайнего сообщения*/
	auto & lastmsg = msg_list_.front();

	switch (lastmsg.code_) {
	case Message::Type::PROG_EXIT:
		runs = false;
		break;
	default:
		break;
	}

	msg_list_.pop_front();
	// delete lastmsg;
}

/*Функция отрабатывает нажатия пользователя */
void Program::input_handle_()
{
	switch (event_.type) {
	default:
		break;
	case SDL_KEYUP:
		if (SDL_SCANCODE_ESCAPE == event_.key.keysym.scancode)
			send_msg(Message{NULL, Message::Type::PROG_EXIT});
		// *runFlag = false;
		if (SDL_SCANCODE_Q == event_.key.keysym.scancode)
			send_msg(Message{NULL, Message::Type::PROG_EXIT});
		// *runFlag = false;
		return;

		if (SDL_WINDOWEVENT_CLOSE == event_.window.event)
			send_msg(Message{NULL, Message::Type::PROG_EXIT});
		// *runFlag = false;

		return;
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
void Program::operator()()
{
	bool runs{true};
	while (runs) { // Обработка событий
		while (SDL_PollEvent(&event_))
			input_handle_();

		msg_handle_(runs);

		// Заливка фона, завершение работы если не удалось
		if (DrawBackground_(rend_, &bgcolour_))
			throw Program::Error(Program::Error::type::SDL,
					     SDL_GetError());

		SDL_RenderPresent(rend_); // Вывод его на экран
		SDL_Delay(frametime_); // Задержка перед новым этапом отрисовки
	}
}

/*Завершение работы программы*/
Program::~Program()
{
	if (rend_)
		SDL_DestroyRenderer(rend_);

	if (win_)
		SDL_DestroyWindow(win_);

	SDL_Quit();
}

/*Запуск программы*/
Program::Program()
{
	/*Запуск SDL*/
	if (SDL_Init(SDL_INIT_VIDEO))
		throw Program::Error(Program::Error::type::SDL, SDL_GetError());

	win_ = SDL_CreateWindow(WinName_.data(), SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, winsize_.x, winsize_.y,
				SDL_WINDOW_SHOWN);
	if (win_ == nullptr)
		throw Program::Error(Program::Error::type::SDL, SDL_GetError());

	rend_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED);
	if (nullptr == rend_)
		throw Program::Error(Program::Error::type::SDL, SDL_GetError());
}

/*Геттер/конструктор объекта программы*/
Program * Program::get()
{
	if (!inst_) {
		if (nullptr == (inst_ = new (std::nothrow) Program))
			throw Program::Error(
				Program::Error::type::BAD_ALLOC,
				"Failed to create Program instance");
	}
	return inst_;
}

/*Начальное значение указателя на объект программы*/
Program * Program::inst_{nullptr};
