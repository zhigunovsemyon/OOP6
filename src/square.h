#pragma once
#include "circle.h"

class Square : public CircleBase {
	constexpr static int polycount_{4};
public:
	Square(int x, int y) : CircleBase{x, y, polycount_} {}
};
