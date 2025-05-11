#include "triangle.h"
#include "program.h"
#include "sdlexcept.h"

bool Triangle::covers_(SDL_Point const & point) const noexcept
{
	if (point.x > pos_.x + wh_.x / 2 || point.x < pos_.x - wh_.x / 2)
		return false;

	if (point.y > pos_.y + wh_.y / 2 || point.y < pos_.y - wh_.y / 2)
		return false;

	return true;
}

void Triangle::taller_() noexcept
{
	constexpr auto maxsize =
		std::min(Program::winsize().y, Program::winsize().x) - step;

	if ((wh_.y = (int)(wh_.y * mult_)) > maxsize)
		wh_.y = maxsize;
}

void Triangle::wider_() noexcept
{
	constexpr auto maxsize =
		std::min(Program::winsize().y, Program::winsize().x) - step;

	if ((wh_.x = (int)(wh_.x * mult_)) > maxsize)
		wh_.x = maxsize;
}

void Triangle::narrower_() noexcept
{
	constexpr auto minsize = 3 * step;

	if ((wh_.x = (int)(wh_.x / mult_)) < minsize)
		wh_.x = minsize;
}

void Triangle::lower_() noexcept
{
	constexpr auto minsize = 3 * step;

	if ((wh_.y = (int)(wh_.y / mult_)) < minsize)
		wh_.y = minsize;
}

void Triangle::draw(SDL_Renderer * rend) const
{
	SDL_Vertex verts[3]; // 3 вершины полигона
	verts[0].color = verts[1].color = verts[2].color = cur_colour();

	verts[0].tex_coord = verts[1].tex_coord = verts[2].tex_coord =
		SDL_FPoint{0.0f, 0.0f};

	verts[0].position =
		SDL_FPoint{(float)(pos_.x - wh_.x / 2), (float)(pos_.y + wh_.y / 2)};
	verts[1].position =
		SDL_FPoint{(float)(pos_.x + wh_.x / 2), (float)(pos_.y + wh_.y / 2)};
	verts[2].position =
		SDL_FPoint{(float)(pos_.x), (float)(pos_.y - wh_.y / 2)};

	if (SDL_RenderGeometry(rend, NULL, verts, 3, NULL, 0))
		throw SDL_exception{};
}