#pragma once
#include <SDL2/SDL.h>
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

	Program(); /*Конструктор программы. Выбрасывает исключения*/
	~Program();/*Деструктор программы*/

	/*Удаление конструктора копирования*/
	Program(Program const &) = delete;

	/*Удаление операции присвоения*/
	Program & operator=(Program const &) = delete;

	/*Диспетчер*/
	int operator()();
};
