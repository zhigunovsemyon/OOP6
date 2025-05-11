#include "rect.h"
#include "sdlexcept.h"
#include "program.h"

bool Rectangle::covers_(SDL_Point const & point) const noexcept
{
	if (point.x > pos_.x + wh_.x / 2 || point.x < pos_.x - wh_.x / 2)
		return false;

	if (point.y > pos_.y + wh_.y / 2 || point.y < pos_.y - wh_.y / 2)
		return false;

	return true;
}

void Rectangle::taller_() noexcept 
{
	constexpr auto maxsize =
		std::min(Program::winsize().y, Program::winsize().x) - step;

	if (wh_.y < maxsize - step)
		wh_.y = (int)(wh_.y * mult_);
}

void Rectangle::wider_() noexcept
{
	constexpr auto maxsize =
		std::min(Program::winsize().y, Program::winsize().x) - step;

	if (wh_.x < maxsize - step)
		wh_.x = (int)(wh_.x * mult_);
}

void Rectangle::narrower_() noexcept
{
	constexpr auto minsize = 3 * step;

	if ((wh_.x = (int)(wh_.x / mult_)) < minsize)
		wh_.x = minsize;
}

void Rectangle::lower_() noexcept
{
	constexpr auto minsize = 3 * step;

	if ((wh_.y = (int)(wh_.y / mult_)) < minsize)
		wh_.y = minsize;
}

void Rectangle::draw(SDL_Renderer * rend) const
{
	SDL_Rect const r{pos_.x - wh_.x / 2, pos_.y - wh_.y / 2, wh_.x, wh_.y};

	if(SDL_SetRenderDrawColor(rend, cur_colour().r, cur_colour().g,
			       cur_colour().b, cur_colour().a))
		throw SDL_exception{};
			       
	if (SDL_RenderFillRect(rend, &r))
		throw SDL_exception{};
}