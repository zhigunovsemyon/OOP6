#pragma once
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
		LCLICK,	   /*Клик ЛКМ*/
		RCLICK,	   /*Клик ПКМ*/
		KB_HIT,	   /*Нажатие на клавиатуру*/
		DESELECT,  /*Удаление объекта из списка*/
		ADDME,	   /*Добавление нового объекта*/
		DELME,	   /*Удаление объекта*/
		PROG_EXIT, /*Завершение работы*/
		FACT_NEXT, /*Следующая фабрика*/
		FACT_PREV, /*Предыдущая фабрика*/
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
	Object * sender_;
public:
	Object * sender() const { return sender_; }

	MessageClear(Object * ptr)
		: Message{Message::Type::DESELECT}, sender_{ptr}
	{
	}
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
		: Message{Message::Type::ADDME}, sender_(ptr)
	{
	}
};

class MessageExit : public Message {
public:
	MessageExit() : Message{Message::Type::PROG_EXIT} {}
};

class MessageBuilderNext : public Message {
public:
	MessageBuilderNext() : Message{Message::Type::FACT_NEXT} {}
};

class MessageBuilderPrev : public Message {
public:
	MessageBuilderPrev() : Message{Message::Type::FACT_PREV} {}
};

class MessageLClick : public Message {
	int x_, y_;

public:
	MessageLClick(int x, int y)
		: Message{Message::Type::LCLICK}, x_{x}, y_{y}
	{
	}

	int x() const { return x_; }

	int y() const { return y_; }
};

class MessageRClick : public Message {
	int x_, y_;

public:
	MessageRClick(int x, int y)
		: Message{Message::Type::RCLICK}, x_{x}, y_{y}
	{
	}

	int x() const { return x_; }

	int y() const { return y_; }
};

class MessageDelete : public Message {
	Object * sender_;

public:
	Object * sender() const { return sender_; }

	MessageDelete(Object * ptr)
		: Message{Message::Type::DELME}, sender_(ptr)
	{
	}
};
