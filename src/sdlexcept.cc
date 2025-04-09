#include "sdlexcept.h"

#include <SDL_error.h>
#ifndef SDL_error_h_
#include <SDL2/SDL_error.h>
#endif // SDL_error_h_

SDL_exception::SDL_exception() : str_{SDL_GetError()} {}

/*Сообщение об ошибке*/
char const * SDL_exception::what() const noexcept
{
	return str_;
}

SDL_exception::~SDL_exception() = default;
