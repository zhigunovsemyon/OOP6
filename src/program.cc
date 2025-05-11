#include <algorithm>
#include <cassert>
#include <memory>
#include <stdexcept>

#include "graphic_obj.h"
#include "message.h"
#include "program.h"
#include "sdlexcept.h"

#include <SDL.h>
#ifndef SDL_h_
#include <SDL2/SDL.h>
#endif // !SDL_h_

#include <SDL_render.h>
#ifndef SDL_render_h_
#include <SDL2/SDL_render.h>
#endif // !SDL_render_h_

#include <SDL_ttf.h>
#ifndef SDL_TTF_H_
#include <SDL2/SDL_ttf.h>
#endif // !SDL_h_

#include <SDL_surface.h>
#ifndef SDL_surface_h_
#include <SDL2/SDL_surface.h>
#endif // !SDL_surface_h_

/*Функция отрабатывает нажатия пользователя */
void Program::input_handle_()
{
	switch (event_.type) {
	default:
		break;
	case SDL_WINDOWEVENT:
		if (SDL_WINDOWEVENT_CLOSE == event_.window.event)
			send_msg(new MessageExit);
		break;
	case SDL_KEYUP:
		send_msg(new MessageKeyboard(event_.key.keysym.scancode));
		break;

	case SDL_MOUSEBUTTONUP:
		if (event_.button.button == SDL_BUTTON_LEFT)
			send_msg(new MessageClick{event_.button.x,
						  event_.button.y});
		break;
	}
}

/*Функция рисования фона рисовальщика rend, цветом r g b*/
static int DrawBackground_(SDL_Renderer * rend, SDL_Colour const * col)
{
	if (SDL_SetRenderDrawColor(rend, col->r, col->g, col->b, col->a) ||
	    SDL_RenderClear(rend)) {
		return 1;
	}
	/*else*/
	return 0;
}

void Program::draw_text(std::string_view txt, SDL_Point const & corner)
{
	auto surf{TTF_RenderUTF8_LCD(font_, txt.data(), TextCol_, bgcolour_)};
	if (!surf)
		throw TTF_exception{};
	SDL_Rect const dest_rect{corner.x, corner.y, surf->w, surf->h};

	auto texture{SDL_CreateTextureFromSurface(rend_, surf)};
	if (!texture) {
		SDL_FreeSurface(surf);
		throw SDL_exception{};
	}

	if (SDL_RenderCopy(rend_, texture, NULL, &dest_rect)) {
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surf);
		throw SDL_exception{};
	}
}


void Program::msg_handle_(bool & runs)
{
	if (msg_list_.empty())
		return;

	/*Извлечение крайнего сообщения*/
	if (msg_list_.front() == nullptr) {
		msg_list_.pop();
		throw std::runtime_error{"nullptr message"};
	}
	auto & lastmsg = *msg_list_.front();
	msg_list_.pop();

	/*Рассылка сообщения по объектам*/
	std::for_each(obj_list_.begin(), obj_list_.end(),
		      [&lastmsg](auto * o) { o->recieve_msg(&lastmsg); });

	switch (lastmsg.code()) {
	case Message::Type::PROG_DEL: {
		auto const & del_msg{dynamic_cast<MessageDelete &>(lastmsg)};
		/*obj_list_.remove_if([&del_msg](auto const * o) {
			return o->covers({del_msg.x(), del_msg.y()});
		});*/
		/*auto del_fn = [&](auto * o) {
			if (o->covers({del_msg.x(), del_msg.y()})) {
				std::erase(obj_list_, o);
				delete o;
			}
		};
		std::for_each(obj_list_.begin(), obj_list_.end(), del_fn);*/
		break;
	}
	case Message::Type::OBJ_CLICK: {
		auto const & click_msg{dynamic_cast<MessageClick &>(lastmsg)};
		interactor_->click({click_msg.x(), click_msg.y()});
		break;
	}
	case Message::Type::OBJ_KBHIT: {
		auto const & kbhit_msg{
			dynamic_cast<MessageKeyboard &>(lastmsg)};
		interactor_->kb_press(kbhit_msg.kbcode());
		break;
	}
	case Message::Type::PROG_EXIT:
		runs = false;
		break;
	case Message::Type::PROG_SPAWN: {
		auto const & spawn_msg{dynamic_cast<MessageSpawn &>(lastmsg)};
		obj_list_.push_front(
			dynamic_cast<GraphicObject *>(spawn_msg.sender()));
		break;
	}
	case Message::Type::PROG_CHMOD: {
		switch (dynamic_cast<MessageChmod &>(lastmsg).mode()) {
		case InteractBase::type():
			interactor_ = &basic_interactor_;
			break;
		case InteractDelete::type():
			interactor_ = &deleter_;
			break;
		case InteractCreate::type():
			interactor_ = &creator_;
			break;
		case InteractResize::type():
			interactor_ = &resizer_;
			break;
		case InteractMove::type():
			interactor_ = &mover_;
			break;
		}
		break;
	}
	default:
		break;
	}

	delete &lastmsg;
}
/*Диспетчер программы*/
Program & Program::run()
{
	bool runs{true};
	while (runs) { // Обработка событий
		while (SDL_PollEvent(&event_))
			input_handle_();

		msg_handle_(runs);

		// Заливка фона, завершение работы если не удалось
		if (DrawBackground_(rend_, &bgcolour_))
			throw SDL_exception{};

		auto rend_link = rend_;
		std::for_each(
			obj_list_.begin(), obj_list_.end(),
			[&rend_link](auto const o) { o->draw(rend_link); });

		SDL_RenderPresent(rend_); // Вывод его на экран
		SDL_Delay(frametime_); // Задержка перед новым этапом отрисовки
	}

	return *this;
}

/*Завершение работы программы*/
Program::~Program()
{
	std::for_each(obj_list_.begin(), obj_list_.end(),
		      [](auto * p) { delete p; });

	/*Очистка остальной очереди сообщений*/
	while (!msg_list_.empty()) {
		auto * top = msg_list_.front();
		delete top;
		msg_list_.pop();
	}

	if (font_)
		TTF_CloseFont(font_);

	if (rend_)
		SDL_DestroyRenderer(rend_);

	if (win_)
		SDL_DestroyWindow(win_);

	TTF_Quit();
	SDL_Quit();
}

/*Запуск программы*/
Program::Program()
{
	/*При неудаче очистка осуществляется сразу в конструкторе,
	т.к. объект не будет создан и не будет вызвано деструктора*/

	/*Запуск SDL*/
	if (SDL_Init(SDL_INIT_VIDEO))
		throw SDL_exception{};

	/*Запуск SDL_ttf*/
	if (TTF_Init()) {
		SDL_Quit();
		throw TTF_exception{};
	}

	win_ = SDL_CreateWindow(WinName_.data(), SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, winsize_.x, winsize_.y,
				SDL_WINDOW_SHOWN);
	if (win_ == nullptr) {
		/*Сохранение строки для передачи в исключение.*/
		auto str = SDL_GetError();
		TTF_Quit();
		SDL_Quit();
		throw SDL_exception{str};
	}

	rend_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED);
	if (nullptr == rend_) {
		/*Сохранение строки для передачи в исключение.*/
		auto str = SDL_GetError();
		SDL_DestroyWindow(win_);
		TTF_Quit();
		SDL_Quit();
		throw SDL_exception{str};
	}

	font_ = TTF_OpenFont(FontPath_.data(), FontSize_);
	if (font_ == nullptr) {
		/*Сохранение строки для передачи в исключение.*/
		auto str = SDL_GetError();
		SDL_DestroyRenderer(rend_);
		SDL_DestroyWindow(win_);
		TTF_Quit();
		SDL_Quit();
		throw TTF_exception{str};
	}

	interactor_ = &basic_interactor_;
}

/*Геттер/конструктор объекта программы. Выкидывает исключение при неудачном
 * создании инстанса*/
Program & Program::get()
{
	/*Создаётся при первом вызове. Живёт всю программу*/
	static Program inst_;
	return inst_;
}
