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
		OBJ_CLICK, /*Клик мышью*/
		OBJ_KBHIT, /*Нажатие на клавиатуру*/
		OBJ_CLEAR, /*Удаление объекта из списка*/
		PROG_SPAWN,/*Добавление нового объекта*/
		PROG_DEL,  /*Поиск объекта для удаления*/
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

class MessageClear : public Message {
public:
	MessageClear() : Message{Message::Type::OBJ_CLEAR} {}
};

class MessageKeyboard : public Message {
	SDL_Scancode kbcode_;

public:
	SDL_Scancode kbcode() const { return kbcode_; }

	MessageKeyboard(SDL_Scancode c)
		: Message{Message::Type::OBJ_KBHIT}, kbcode_(c)
	{
	}
};

class MessageSpawn : public Message {
	Object * sender_;

public:
	Object * sender() const { return sender_; }

	MessageSpawn(Object * ptr)
		: Message{Message::Type::PROG_SPAWN}, sender_(ptr)
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
		: Message{Message::Type::OBJ_CLICK}, x_{x}, y_{y}
	{
	}

	int x() const { return x_; }

	int y() const { return y_; }
};

class MessageDelete : public Message {
	int x_, y_;

public:
	MessageDelete(int x, int y)
		: Message{Message::Type::PROG_DEL}, x_{x}, y_{y}
	{
	}

	int x() const { return x_; }

	int y() const { return y_; }
};
