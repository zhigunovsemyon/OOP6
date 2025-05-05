#pragma once
#include <exception>

class TTF_exception : public std::exception {
private:
	char const * str_;

public:
	TTF_exception();

	/*Сообщение об ошибке*/
	char const * what() const noexcept override;

	~TTF_exception() override;
};
