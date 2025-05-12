#pragma once
#include "circle.h"

class Square : public CircleBase {
	friend class SquareBuilder;
	constexpr static int polycount_{4};

	Square(int x, int y) : CircleBase{x, y, polycount_} {}
};

class SquareBuilder : public GraphicBuilder {
public:
	SquareBuilder() noexcept {}
	GraphicObject * create(int x, int y) const override
	{
		return new Square {x,y};
	}
};
