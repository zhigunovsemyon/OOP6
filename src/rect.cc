#include "rect.h"
#include "program.h"
#include "sdlexcept.h"

bool Rectangle::covers_(SDL_Point const & point) const noexcept
{
	bool const to_the_right = point.x > pos_.x + wh_.x / 2;
	bool const to_the_left = point.x < pos_.x - wh_.x / 2;
	if (to_the_right || to_the_left)
		return false;

	bool const above = point.y < pos_.y - wh_.y / 2;
	bool const below = point.y > pos_.y + wh_.y / 2;
	if (above || below)
		return false;

	return true;
}

void Rectangle::taller_() noexcept
{
	constexpr auto maxsize = std::min(Program::winsize().y, Program::winsize().x) - step;

	wh_.y = (int)((float)wh_.y * mult_);
	if (wh_.y > maxsize)
		wh_.y = maxsize;
}

void Rectangle::wider_() noexcept
{
	constexpr auto maxsize = std::min(Program::winsize().y, Program::winsize().x) - step;

	wh_.x = (int)((float)wh_.x * mult_);
	if (wh_.x > maxsize)
		wh_.x = maxsize;
}

void Rectangle::narrower_() noexcept
{
	constexpr auto minsize = 3 * step;

	wh_.x = (int)((float)wh_.x / mult_);
	if (wh_.x < minsize)
		wh_.x = minsize;
}

void Rectangle::lower_() noexcept
{
	constexpr auto minsize = 3 * step;

	wh_.y = (int)((float)wh_.y / mult_);
	if (wh_.y < minsize)
		wh_.y = minsize;
}

void Rectangle::draw(SDL_Renderer * rend) const
{
	SDL_Point const nw_corner{pos_.x - wh_.x / 2, pos_.y - wh_.y / 2};
	SDL_Rect const r{nw_corner.x, nw_corner.y, wh_.x, wh_.y};

	if (SDL_SetRenderDrawColor(rend, cur_colour().r, cur_colour().g, cur_colour().b, cur_colour().a))
		throw SDL_exception{};

	if (SDL_RenderFillRect(rend, &r))
		throw SDL_exception{};
}
