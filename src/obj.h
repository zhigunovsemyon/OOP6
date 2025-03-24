#pragma once

/*Опережающее объявление класса сообщений из message.h*/
class Message;

class Object {
private:

public:
	virtual ~Object() = default;

	/*Метод передачи сообщения инстансу программы*/
	void send_msg(Message && msg);

	/*Интерфейс получения сообщения*/
	virtual void recieve_msg() = 0;
};
