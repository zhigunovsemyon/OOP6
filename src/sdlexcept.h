#pragma once
#include <stdexcept>

class SDL_exception : public std::runtime_error {
public:
	~SDL_exception() override;
	SDL_exception() noexcept;
	SDL_exception(char const *) noexcept;
};
