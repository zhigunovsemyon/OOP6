#pragma once
#include "graphic_obj.h"
#include "message.h"

class CircleBase : public GraphicObject {
public:
	void draw(SDL_Renderer *) const override;

	// void recieve_msg(Message *) override;

	~CircleBase() override = default;

private:
	constexpr static int default_radius_{64};
	int const polycount_;

	int radius_;

protected:
	CircleBase(int x, int y, int pc)
		: GraphicObject{x, y}, radius_{default_radius_}, polycount_{pc}
	{
	}

	bool covers_(SDL_Point const &) const noexcept override;

	void bigger_() noexcept override;
	void smaller_() noexcept override;

	void taller_() noexcept override { bigger_(); }

	void wider_() noexcept override { bigger_(); }

	void narrower_() noexcept override { smaller_(); }

	void lower_() noexcept override { smaller_(); }
};

class Circle : public CircleBase {
	static constexpr int polycount_{20};

public:
	Circle(int x, int y) : CircleBase{x, y, polycount_} {}
};