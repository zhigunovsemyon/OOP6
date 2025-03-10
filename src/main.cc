#include "program.h"
#include <cassert>
#include <iostream>

int main()
try {
	auto prog{Program::get()};
	(*prog)();
	prog->quit();

	return EXIT_SUCCESS;
} catch (Program::Error err) {
	assert(err.fail());
	switch (err.code) {
	case (Program::Error::type::BAD_ALLOC):
		std::cerr << "Ошибка new: " << err.str();
		break;
	case (Program::Error::type::SDL):
		std::cerr << "Ошибка SDL: " << err.str();
		break;
		return static_cast<int>(err.code);
	}
}
