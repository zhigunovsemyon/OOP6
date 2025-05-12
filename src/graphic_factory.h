#pragma once
#include "graphic_obj.h"
#include <span>

class GraphicFactory : public GraphicBuilder {
	std::span<GraphicBuilder *> ext_;
	std::span<GraphicBuilder *>::const_iterator i_;

public:
	GraphicFactory(std::span<GraphicBuilder *> ext)
		: ext_{ext}, i_{ext_.cbegin()}
	{
	}

	~GraphicFactory() = default;

	virtual GraphicObject * create(int x, int y) const override
	{
		return (*i_)->create(x, y);
	}

	void prev() noexcept
	{
		i_ = i_ == ext_.cbegin() ? ext_.cend() - 1 : std::prev(i_);
	}

	void next() noexcept
	{
		i_ = std::next(i_) == ext_.end() ? ext_.cbegin()
						 : std::next(i_);
	}
};
