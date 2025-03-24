#pragma once
#include "obj.h"

class Message {
private:
	/*sender_ -- отправитель сообщения, reciever_ -- получатель,
	 * либо nullptr, если сообщение адресовано всем*/
	[[maybe_unused]] Object *sender_, *reciever_;

public:
	enum class Type {
		NIL,	   /*Пустое сообщение*/
		MS_CLICK,  /*Клик мышью*/
		KB_HIT,	   /*Нажатие на клавиатуру*/
		OBJ_SPAWN, /*Появление нового объекта*/
		OBJ_DEL,   /*Удаление объекта*/
		PROG_EXIT  /*Завершение работы*/
	} code_;

	Message(Object * sender,
		Message::Type code = Message::Type::NIL,
		Object * reciever = nullptr)
		: sender_(sender), reciever_(reciever), code_{code}
	{
	}

	Message(Message && ot)
		: sender_(ot.sender_), reciever_(ot.reciever_), code_{ot.code_}
	{
		ot.code_ = Message::Type::NIL;
		ot.reciever_ = ot.sender_ = nullptr;
	}

	void clear() { code_ = Message::Type::NIL; }
};
