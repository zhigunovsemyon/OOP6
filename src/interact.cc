#include "interact.h"
#include "program.h"

void InteractMove::click(SDL_Point const &) {}

void InteractDelete::click(SDL_Point const &) {}

void InteractResize::click(SDL_Point const &) {}

#include "circle.h"

void InteractCreate::click(SDL_Point const & point)
{
	new Circle{point.x, point.y};
}

void InteractMove::kb_press(SDL_Scancode c) const
{
	if (SDL_SCANCODE_Q == c)
		Program::get().send_msg(new MessageExit);
	if (SDL_SCANCODE_ESCAPE == c)
		Program::get().send_msg(new MessageChmod{InteractBase::type()});
}

void InteractDelete::kb_press(SDL_Scancode c) const
{
	if (SDL_SCANCODE_Q == c)
		Program::get().send_msg(new MessageExit);
	if (SDL_SCANCODE_ESCAPE == c)
		Program::get().send_msg(new MessageChmod{InteractBase::type()});
}

void InteractCreate::kb_press(SDL_Scancode c) const
{
	if (SDL_SCANCODE_Q == c)
		Program::get().send_msg(new MessageExit);
	if (SDL_SCANCODE_ESCAPE == c)
		Program::get().send_msg(new MessageChmod{InteractBase::type()});
}

void InteractResize::kb_press(SDL_Scancode c) const
{
	if (SDL_SCANCODE_Q == c)
		Program::get().send_msg(new MessageExit);
	if (SDL_SCANCODE_ESCAPE == c)
		Program::get().send_msg(new MessageChmod{InteractBase::type()});
}

void InteractBase::kb_press(SDL_Scancode c) const
{
	switch (c) {
	case SDL_SCANCODE_Q:
	case SDL_SCANCODE_ESCAPE:
		Program::get().send_msg(new MessageExit);
		break;
	case SDL_SCANCODE_M:
		Program::get().send_msg(new MessageChmod{InteractMove::type()});
		break;
	case SDL_SCANCODE_R:
		Program::get().send_msg(
			new MessageChmod{InteractResize::type()});
		break;
	case SDL_SCANCODE_D:
		Program::get().send_msg(
			new MessageChmod{InteractDelete::type()});
		break;
	case SDL_SCANCODE_C:
		Program::get().send_msg(
			new MessageChmod{InteractCreate::type()});
		break;
	default:
		break;
	}
}