#pragma once
#include "graphic_obj.h"
#include <span>

class GraphicFactory {
	std::span<GraphicBuilder *> ext_;
	int i;

public:
	GraphicFactory(std::span<GraphicBuilder *> ext)
		: ext_{ext}, i{(int)ext.size() - 1}
	{
	}

	~GraphicFactory() = default;

	void make(int x, int y) const { ext_[(size_t)i]->create(x, y); };

	void prev() noexcept
	{
		if (--i < 0)
			i = (int)ext_.size() - 1;
	}

	void next() noexcept
	{
		if (++i >= (int)ext_.size())
			i = 0;
	}
};
