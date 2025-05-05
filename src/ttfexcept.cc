#include "ttfexcept.h"

#include <SDL_ttf.h>
#ifndef SDL_TTF_H_
#include <SDL2/SDL_ttf.h>
#endif // !SDL_h_

TTF_exception::TTF_exception() : std::runtime_error{TTF_GetError()} {}

TTF_exception::~TTF_exception() = default;
