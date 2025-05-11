#include "sdlexcept.h"

#include <SDL_error.h>
#ifndef SDL_error_h_
#include <SDL2/SDL_error.h>
#endif // SDL_error_h_

#include <SDL_ttf.h>
#ifndef SDL_TTF_H_
#include <SDL2/SDL_ttf.h>
#endif // !SDL_TTF_H_

SDL_exception::SDL_exception() noexcept : std::runtime_error{SDL_GetError()} {}

SDL_exception::SDL_exception(char const * str) noexcept
	: std::runtime_error{str}
{
}

SDL_exception::~SDL_exception() = default;

TTF_exception::TTF_exception() noexcept : std::runtime_error{TTF_GetError()} {}

TTF_exception::TTF_exception(char const * str) noexcept
	: std::runtime_error{str}
{
}

TTF_exception::~TTF_exception() = default;