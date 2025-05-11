#pragma once
#include "graphic_obj.h"

class Rectangle : public GraphicObject {
	friend class RectangleBuilder;
	static constexpr int default_width_{80};
	static constexpr int default_height_{45};
	static constexpr float mult_{1.1f};

	SDL_Point wh_;

	bool covers_(SDL_Point const &) const noexcept override;

	void bigger_() noexcept override { taller_(), wider_(); }

	void smaller_() noexcept override { narrower_(), lower_(); }

	void taller_() noexcept override;

	void wider_() noexcept override;

	void narrower_() noexcept override;

	void lower_() noexcept override;

	Rectangle(int x, int y) : GraphicObject{x, y}, wh_{default_width_, default_height_} {}

public:
	void draw(SDL_Renderer *) const override;
};

class RectangleBuilder : public GraphicBuilder {
	GraphicObject * create(int x, int y) override
	{
		return new Rectangle(x, y);
	}
};