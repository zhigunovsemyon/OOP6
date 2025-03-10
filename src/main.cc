#include "program.h"
#include <cassert>
#include <iostream>

int main()
{
	try {
		return Program{}();
	} catch (Program::Error err) {
		assert(err.fail());
		if (err.code == Program::Error::type::SDL) {
			std::cerr << "Ошибка SDL: " << err.str();
			return static_cast<int>(err.code);
		}
	}
}
