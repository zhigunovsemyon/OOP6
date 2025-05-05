#include "sdlexcept.h"

#include <SDL_error.h>
#ifndef SDL_error_h_
#include <SDL2/SDL_error.h>
#endif // SDL_error_h_

SDL_exception::SDL_exception() : std::runtime_error{SDL_GetError()} {}
SDL_exception::SDL_exception(const char * str) : std::runtime_error{str} {}

SDL_exception::~SDL_exception() = default;
