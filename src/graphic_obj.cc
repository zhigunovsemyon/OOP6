#include "graphic_obj.h"
#include "program.h"

void GraphicObject::left_() noexcept
{
	if (pos_.x > 0)
		pos_.x -= step;
}

void GraphicObject::right_() noexcept
{
	if (pos_.x < Program::winsize().x)
		pos_.x += step;
}

void GraphicObject::down_() noexcept
{
	if (pos_.y < Program::winsize().y)
		pos_.y += step;
}

void GraphicObject::up_() noexcept
{
	if (pos_.y > 0)
		pos_.y -= step;
}

void GraphicObject::recieve_msg(Message * msg)
{
	switch (msg->code()) {
	case Message::Type::KB_HIT: {
		if (!selected_)
			return;
		auto const & kb_msg{dynamic_cast<MessageKeyboard &>(*msg)};
		switch (kb_msg.kbcode()) {
		case SDL_SCANCODE_UP:
			up_();
			break;
		case SDL_SCANCODE_DOWN:
			down_();
			break;
		case SDL_SCANCODE_LEFT:
			left_();
			break;
		case SDL_SCANCODE_RIGHT:
			right_();
			break;
		case SDL_SCANCODE_MINUS:
			smaller_();
			break;
		case SDL_SCANCODE_EQUALS:
			bigger_();
			break;
		case SDL_SCANCODE_T:
			taller_();
			break;
		case SDL_SCANCODE_N:
			narrower_();
			break;
		case SDL_SCANCODE_L:
			lower_();
			break;
		case SDL_SCANCODE_W:
			wider_();
			break;
		case SDL_SCANCODE_ESCAPE:
			selected_ = false;
			send_msg(new MessageClear{this});
			break;
		default:
			break;
		}
		msg->clear();
		break;
	}
	case Message::Type::LCLICK: {
		auto const & click_msg{dynamic_cast<MessageLClick &>(*msg)};
		SDL_Point const click_point{click_msg.x(), click_msg.y()};
		if (covers_(click_point)) {
			selected_ = !selected_;
			send_msg(new MessageClear{this});
			msg->clear();
		}
		break;
	}
	case Message::Type::RCLICK: {
		auto const & click_msg{dynamic_cast<MessageRClick &>(*msg)};
		SDL_Point const click_point{click_msg.x(), click_msg.y()};
		if (covers_(click_point)) {
			send_msg(new MessageDelete{this});
			msg->clear();
		}
		break;
	}
	case Message::Type::DESELECT: {
		if (this != dynamic_cast<MessageClear &>(*msg).sender())
			selected_ = false;
		break;
	}
	default:
		break;
	}
}
