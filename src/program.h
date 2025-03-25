#pragma once

#include "graphic_obj.h"
#include "message.h"
#include "obj.h"

#include <SDL2/SDL.h>
#include <deque>
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

	std::deque<Message> msg_list_{};
	std::deque<GraphicObject *> obj_list_{};

	Program(); /*Конструктор программы. Выбрасывает исключения*/

	/*Обработка ввода*/
	void input_handle_();

	/*Обработка сообщений*/
	void msg_handle_(bool & runs);

	~Program(); /*Деструктор программы*/

public:
	class Error : public std::exception {
	private:
		bool fail_;
		std::string_view str_;

	public:
		enum class type {
			SDL = 1,
			BAD_ALLOC = 2
		} code;

		Error(Error::type t, std::string_view str)
			: fail_{true}, str_{str}, code{t}
		{
		}

		/*Находится ли программа в ошибке*/
		bool fail() { return fail_; }

		/*Сообщение об ошибке*/
		char const * what() const noexcept override
		{
			return str_.data();
		}

		~Error() override = default;
	};

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
