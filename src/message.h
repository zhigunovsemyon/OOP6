#pragma once
#include "interact.h"
#include "obj.h"

#include <SDL_keyboard.h>
#ifndef SDL_keyboard_h_
#include <SDL2/SDL_keyboard.h>
#endif // !SDL_keyboard_h_

class Message {
public:
	/*Возможные сообщения*/
	enum class Type {
		NIL,	   /*Пустое сообщение*/
		MS_CLICK,  /*Клик мышью*/
		KB_HIT,	   /*Нажатие на клавиатуру*/
		OBJ_SPAWN, /*Появление нового объекта*/
		OBJ_DEL,   /*Удаление объекта*/
		PROG_EXIT, /*Завершение работы*/
		PROG_CHMOD /*Изменение режима работы программы*/
	};

	virtual ~Message() = default;

	void clear() noexcept { code_ = Message::Type::NIL; }

	Message::Type code() const noexcept { return code_; }

protected:
	Message(Message::Type code) noexcept : code_{code} {}

	Message(Message && ot) noexcept : code_{ot.code_}
	{
		ot.code_ = Message::Type::NIL;
	}

	/*Код сообщения*/
	Type code_;
};

class MessageKeyboard : public Message {
	SDL_Scancode kbcode_;

public:
	SDL_Scancode kbcode() const { return kbcode_; }

	MessageKeyboard(SDL_Scancode c)
		: Message{Message::Type::KB_HIT}, kbcode_(c)
	{
	}
};

class MessageSpawn : public Message {
	Object * sender_;

public:
	Object * sender() const { return sender_; }

	MessageSpawn(Object * ptr)
		: Message{Message::Type::OBJ_SPAWN}, sender_(ptr)
	{
	}
};

class MessageDelete : public Message {
	Object * sender_;

public:
	Object * sender() const { return sender_; }

	MessageDelete(Object * ptr)
		: Message{Message::Type::OBJ_DEL}, sender_(ptr)
	{
	}
};

class MessageChmod : public Message {
	InteractBase::Type t_;

public:
	InteractBase::Type mode() const { return t_; }

	MessageChmod(InteractBase::Type t)
		: Message{Message::Type::PROG_CHMOD}, t_{t}
	{
	}
};

class MessageExit : public Message {
public:
	MessageExit() : Message{Message::Type::PROG_EXIT} {}
};

class MessageClick : public Message {
	int x_, y_;

public:
	MessageClick(int x, int y)
		: Message{Message::Type::MS_CLICK}, x_{x}, y_{y}
	{
	}

	int x() const { return x_; }

	int y() const { return y_; }
};
