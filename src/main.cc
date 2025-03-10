#include <SDL2/SDL.h>
#include <iostream>
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
	static bool running_;

public:
	class Error {
	private:
		bool fail_;
		std::string_view str_;

	public:
		enum class type {
			SDL = 1
		} code;

		Error(Error::type t, std::string_view str)
			: fail_{true}, str_{str}, code{t}
		{
		}

		/*Находится ли программа в ошибке*/
		bool fail() { return fail_; }

		/*Сообщение об ошибке*/
		std::string_view str() { return str_; }
	};

	Program();
	~Program();

	void operator()();
};

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
bool DrawBackground(SDL_Renderer * rend, SDL_Colour const & col) noexcept
{
	if (SDL_SetRenderDrawColor(rend, col.r, col.g, col.b, col.a) ||
	    SDL_RenderClear(rend)) {
		return true;
	}
	/*else*/
	return false;
}

void Program::operator()()
{
	bool runs{true};
	while (runs) { // Обработка событий
		while (SDL_PollEvent(&event_))
			EventHandler(&runs, &event_);

		// Заливка фона, завершение работы если не удалось
		if (DrawBackground(rend_, bgcolour_))
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

	running_ = false;
}

/*Запуск программы*/
Program::Program()
{
	/*Если программа уже работает*/
	if (running_)
		return;

	running_ = true; /*Установка флага работы программы*/

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

bool Program::running_{false};

int main()
{
	try {
		Program{}();
	} catch (Program::Error err) {
		if (err.code == Program::Error::type::SDL) {
			std::cerr << "Ошибка SDL: " << err.str();
			return static_cast<int>(err.code);
		}
	}
}
