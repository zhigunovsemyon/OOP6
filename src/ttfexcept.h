#pragma once
#include <stdexcept>

class TTF_exception : public std::runtime_error {
public:
	~TTF_exception() override;
	TTF_exception();
};
