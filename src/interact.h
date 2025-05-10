#pragma once

#include <SDL_rect.h>
#ifndef SDL_rect_h_
#include <SDL2/SDL_rect.h>
#endif // !SDL_rect_h_

class InteractBase {
public:
	enum class Type {
		MOVER,
		RESIZER,
		CREATOR,
		DELETER
	};
	virtual ~InteractBase() = default;
	virtual void click(SDL_Point const &) = 0;

	InteractBase::Type type() const { return t_; }

private:
	Type t_;
};

class InteractMove : public InteractBase {
public:
	void click(SDL_Point const &) override;
};

class InteractResize : public InteractBase {
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
