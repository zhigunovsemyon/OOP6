#pragma once
#include <exception>

class SDL_exception : public std::exception {
private:
	char const * str_;

public:
	SDL_exception();

	/*Сообщение об ошибке*/
	char const * what() const noexcept override;

	~SDL_exception() override;
};
