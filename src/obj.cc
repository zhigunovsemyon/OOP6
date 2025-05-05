#include "program.h"
#include "message.h"
#include <utility>
#include "obj.h"

void Object::send_msg(Message && msg)
{
	Program::get().send_msg(std::move(msg));
}
