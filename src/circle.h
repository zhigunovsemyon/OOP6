#pragma once
#include "graphic_obj.h"
#include "message.h"

class Circle : public GraphicObject {
public:
	void draw(SDL_Renderer *) const override;
	void recieve_msg(Message *) override;

	Circle(int x, int y) : GraphicObject{x, y}, radius_{default_radius_} {}

	~Circle() override = default;

private:
	constexpr static int default_radius_{64};
	constexpr static int polycount_{18};


	int radius_;

protected:
	bool covers_(SDL_Point const &) const override;
};
