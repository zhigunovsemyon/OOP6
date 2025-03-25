#include "program.h"
#include <cassert>
#include <iostream>

int main(int, char *[])
try {
	auto prog{Program::get()};
	prog->run();
	prog->quit();

	return EXIT_SUCCESS;
} catch (std::exception & err) {
	Program::Error * myerr{dynamic_cast<Program::Error *>(&err)};
	if (!myerr) {
		std::cerr << "Ошибка не предусмотрена в Program::Error. "
			  << "Сообщение: " << err.what() << '\n';
		Program::get()->quit();
		return -1;
	}

	assert(myerr->fail());
	switch (myerr->code) {
	case (Program::Error::type::BAD_ALLOC):
		std::cerr << "Ошибка new: " << err.what();
		break;
	case (Program::Error::type::SDL):
		std::cerr << "Ошибка SDL: " << err.what();
		break;
	}
	Program::get()->quit();
	return static_cast<int>(myerr->code);
}
