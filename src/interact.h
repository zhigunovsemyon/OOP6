#pragma once

#include <SDL_rect.h>
#ifndef SDL_rect_h_
#include <SDL2/SDL_rect.h>
#endif // !SDL_rect_h_

#include <SDL_keyboard.h>
#ifndef SDL_keyboard_h_
#include <SDL2/SDL_keyboard.h>
#endif // !SDL_keyboard_h_

class InteractBase {
public:
	enum class Type {
		MOVER,
		RESIZER,
		CREATOR,
		DELETER,
		BASIC
	};
	virtual ~InteractBase() = default;
	virtual void click(SDL_Point const &){};

	virtual void kb_press(SDL_Scancode) const;

	static constexpr InteractBase::Type type()
	{
		return InteractBase::Type::BASIC;
	}
};

class InteractMove : public InteractBase {
public:
	void kb_press(SDL_Scancode) const override;
	void click(SDL_Point const &) override;

	static constexpr InteractBase::Type type()
	{
		return InteractBase::Type::MOVER;
	}
};

class InteractResize : public InteractBase {
public:
	void kb_press(SDL_Scancode) const override;
	void click(SDL_Point const &) override;

	static constexpr InteractBase::Type type()
	{
		return InteractBase::Type::RESIZER;
	}
};

class InteractDelete : public InteractBase {
public:
	void kb_press(SDL_Scancode) const override;
	void click(SDL_Point const &) override;

	static constexpr InteractBase::Type type()
	{
		return InteractBase::Type::DELETER;
	}
};

class InteractCreate : public InteractBase {
public:
	void click(SDL_Point const &) override;
	void kb_press(SDL_Scancode) const override;

	static constexpr InteractBase::Type type()
	{
		return InteractBase::Type::CREATOR;
	}
};
