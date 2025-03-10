#include "program.h"
#include "obj.h"
#include <cassert>

/*Функция отрабатывает нажатия пользователя в ev, меняет размер screenSize окна
 * wind и ход выполнения программы runFlag*/
void EventHandler(bool * runFlag, SDL_Event * ev)
{
	switch (ev->type) {
	default:
		break;
	case SDL_KEYUP:
		if (SDL_SCANCODE_ESCAPE == ev->key.keysym.scancode)
			*runFlag = false;
		if (SDL_SCANCODE_Q == ev->key.keysym.scancode)
			*runFlag = false;
		return;

		if (SDL_WINDOWEVENT_CLOSE == ev->window.event)
			*runFlag = false;

		return;
	}
}

/*Функция рисования фона рисовальщика rend, цветом r g b*/
int DrawBackground(SDL_Renderer * rend, SDL_Colour const * col)
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
			EventHandler(&runs, &event_);

		// Заливка фона, завершение работы если не удалось
		if (DrawBackground(rend_, &bgcolour_))
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
