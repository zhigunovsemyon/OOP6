#include "ttfexcept.h"

#include <SDL_ttf.h>
#ifndef SDL_TTF_H_
#include <SDL2/SDL_ttf.h>
#endif // !SDL_h_

TTF_exception::TTF_exception() : str_{TTF_GetError()} {}

/*Сообщение об ошибке*/
char const * TTF_exception::what() const noexcept
{
	return str_;
}

TTF_exception::~TTF_exception() = default;
