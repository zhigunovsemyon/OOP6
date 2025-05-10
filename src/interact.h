#pragma once

#include <SDL_rect.h>
#ifndef SDL_rect_h_
#include <SDL2/SDL_rect.h>
#endif // !SDL_rect_h_

class InteractBase {
public:
	virtual ~InteractBase() = default;
	virtual void click(SDL_Point const &) = 0;
};

class InteractMove : public InteractBase {
public:
	void click(SDL_Point const &) override;
};

class InteractDelete : public InteractBase {
public:
	void click(SDL_Point const &) override;
};

class InteractCreate : public InteractBase {
public:
	void click(SDL_Point const &) override;
};
