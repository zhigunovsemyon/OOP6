#pragma once
#include <stdexcept>

class SDL_exception : public std::runtime_error {
public:
	~SDL_exception() override;
	SDL_exception() noexcept;
	SDL_exception(char const *) noexcept;
};

class TTF_exception : public std::runtime_error {
public:
	~TTF_exception() override;
	TTF_exception() noexcept;
	TTF_exception(char const *) noexcept;
};
