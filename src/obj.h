#pragma once

/*Опережающее объявление класса сообщений из message.h*/
class Message;

class Object {
private:

protected:
	virtual ~Object() = default;

	/*Метод передачи сообщения инстансу программы*/
	void send_msg(Message *);

public:
	/*Интерфейс получения сообщения*/
	virtual void recieve_msg(Message *) = 0;
};
