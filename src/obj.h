#pragma once

/*Опережающее объявление класса сообщений из message.h*/
class Message;

class Object {
private:

protected:
	Object() = default;

	/*Метод передачи сообщения инстансу программы*/
	void send_msg(Message *);

public:
	virtual ~Object() = default;

	/*Интерфейс получения сообщения*/
	virtual void recieve_msg(Message *) = 0;
};
