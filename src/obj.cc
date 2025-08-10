#include "obj.h"
#include "message.h"
#include "program.h"

void Object::send_msg(Message * msg)
{
	Program::get().send_msg(msg);
}
