#include "triangle.h"
#include "program.h"
#include "sdlexcept.h"

bool Triangle::covers_(SDL_Point const & point) const noexcept
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

void Triangle::taller_() noexcept
{
	constexpr auto maxsize =
		std::min(Program::winsize().y, Program::winsize().x) - step;

	wh_.y = (int)((float)wh_.y * mult_);
	if (wh_.y > maxsize)
		wh_.y = maxsize;
}

void Triangle::wider_() noexcept
{
	constexpr auto maxsize =
		std::min(Program::winsize().y, Program::winsize().x) - step;

	wh_.x = (int)((float)wh_.x * mult_);
	if (wh_.x < maxsize)
		wh_.x = maxsize;
}

void Triangle::narrower_() noexcept
{
	constexpr auto minsize = 3 * step;

	wh_.x = (int)((float)wh_.x / mult_);
	if (wh_.x < minsize)
		wh_.x = minsize;
}

void Triangle::lower_() noexcept
{
	constexpr auto minsize = 3 * step;

	wh_.y = (int)((float)wh_.y / mult_);
	if (wh_.y < minsize)
		wh_.y = minsize;
}

void Triangle::draw(SDL_Renderer * rend) const
{
	SDL_Vertex verts[3]; // 3 вершины полигона
	verts[0].color = verts[1].color = verts[2].color = cur_colour();

	verts[0].tex_coord = verts[1].tex_coord = verts[2].tex_coord =
		SDL_FPoint{0.0f, 0.0f};

	float const leftmost_line{(float)(pos_.x - wh_.x / 2)};
	float const rightmost_line{leftmost_line + wh_.x};
	float const north_line{(float)(pos_.y - wh_.y / 2)};
	float const south_line{north_line + wh_.y};

	verts[0].position = SDL_FPoint{leftmost_line, south_line};
	verts[1].position = SDL_FPoint{rightmost_line, south_line};
	verts[2].position = SDL_FPoint{(float)pos_.x, north_line};

	if (SDL_RenderGeometry(rend, NULL, verts, 3, NULL, 0))
		throw SDL_exception{};
}
