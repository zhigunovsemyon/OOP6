#pragma once
#include "obj.h"

class Message {
public:
	/*Возможные сообщения*/
	enum class Type {
		NIL,	   /*Пустое сообщение*/
		MS_CLICK,  /*Клик мышью*/
		KB_HIT,	   /*Нажатие на клавиатуру*/
		OBJ_SPAWN, /*Появление нового объекта*/
		OBJ_DEL,   /*Удаление объекта*/
		PROG_EXIT  /*Завершение работы*/
	};

	Message(Object * sender,
		Message::Type code = Message::Type::NIL,
		Object * reciever = nullptr) noexcept
		: sender_(sender), reciever_(reciever), code_{code}
	{
	}

	Message(Message && ot) noexcept
		: sender_(ot.sender_), reciever_(ot.reciever_), code_{ot.code_}
	{
		ot.code_ = Message::Type::NIL;
		ot.reciever_ = ot.sender_ = nullptr;
	}

	void clear() noexcept { code_ = Message::Type::NIL; }

	Message::Type code() const noexcept { return code_; }

	Object * sender() const noexcept { return sender_; }

	Object * reciever() const noexcept { return reciever_; }

private:
	/*sender_ -- отправитель сообщения, reciever_ -- получатель,
	 * либо nullptr, если сообщение адресовано всем*/
	Object *sender_, *reciever_;

	/*Код сообщения*/
	Type code_;
};
