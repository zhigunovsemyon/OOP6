#include "circle.h"
#include "program.h"
#include "sdlexcept.h"

/*Рисование круга рисовальщиком rend, радиуса rad, c центром в pos, цвета col,
с числом полигонов circle_presicion Возвращает 0 при штатной работе, либо 1*/
static int DrawCircle(SDL_Renderer * rend,
		      int rad,
		      SDL_Point centre,
		      SDL_Colour const * col,
		      int circle_presicion)
{
	SDL_Vertex verts[3]; // 3 вершины полигона
	verts[0].color = verts[1].color = verts[2].color = *col;

	verts[0].tex_coord = verts[1].tex_coord = verts[2].tex_coord =
		SDL_FPoint{0.0f, 0.0f};

	// Определение вершины, расположенной в центре круга на всех полигонах
	verts[0].position = SDL_FPoint{(float)centre.x, (float)centre.y};

	for (int i = 0; i < circle_presicion; ++i) {
		// Определение остальных вершин полигонов, сдвинутых на углы
		//(i / кол-во полигонов) и (1+i / кол-во полигонов)
		verts[1].position.x =
			(float)centre.x +
			(float)rad * SDL_cosf(2 * (float)M_PI * (float)(i + 1) /
					      (float)circle_presicion);
		verts[1].position.y =
			(float)centre.y -
			(float)rad * SDL_sinf(2 * (float)M_PI * (float)(i + 1) /
					      (float)circle_presicion);
		verts[2].position.x =
			(float)centre.x +
			(float)rad * SDL_cosf(2 * (float)M_PI * (float)i /
					      (float)circle_presicion);
		verts[2].position.y =
			(float)centre.y -
			(float)rad * SDL_sinf(2 * (float)M_PI * (float)i /
					      (float)circle_presicion);

		// Рисование каждого полигона, возврат кода ошибки при её
		// возникновении
		if (SDL_RenderGeometry(rend, NULL, verts, 3, NULL, 0))
			return 1;
	}
	return 0;
}

void CircleBase::bigger_() noexcept
{
	constexpr auto maxsize =
		std::min(Program::winsize().y, Program::winsize().x) - step;

	if (radius_ * 2 < maxsize)
		radius_ += step;
}

void CircleBase::smaller_() noexcept
{
	if (radius_ > step * 2)
		radius_ -= step;
}

void CircleBase::draw(SDL_Renderer * rend) const
{
	auto const used_col {cur_colour()};
	if (DrawCircle(rend, radius_, pos_, &used_col, polycount_))
		throw SDL_exception{};
}

bool CircleBase::covers_(SDL_Point const & point) const noexcept
{
	/*Не входит в ширину круга*/
	if (point.x > pos_.x + radius_ || point.x < pos_.x - radius_)
		return false;

	/*Не входит в высоту круга*/
	if (point.y > pos_.y + radius_ || point.y < pos_.y - radius_)
		return false;

	return true;
}
