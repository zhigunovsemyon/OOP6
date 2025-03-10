#pragma once
#include "obj.h"

class Message {
private:
	/*sender_ -- отправитель сообщения, reciever_ -- получатель,
	 * либо nullptr, если сообщение адресовано всем*/
	Object *sender_, *reciever_;
	enum class Type {
		NIL,	   /*Пустое сообщение*/
		MS_CLICK,  /*Клик мышью*/
		KB_HIT,	   /*Нажатие на клавиатуру*/
		OBJ_SPAWN, /*Появление нового объекта*/
		OBJ_DEL,   /*Удаление объекта*/
		PROG_EXIT  /*Завершение работы*/
	} code_;

public:
	Message(Object * sender,
		Message::Type code = Message::Type::NIL,
		Object * reciever = nullptr)
		: sender_(sender), code_{code}, reciever_(reciever)
	{
	}

	void clear() { code_ = Message::Type::NIL; }
};
