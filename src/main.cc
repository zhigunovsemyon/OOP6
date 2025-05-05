#include "program.h"
#include "sdlexcept.h"

#include <cassert>
#include <iostream>

int main(int, char *[])
try {
	// auto prog{Program::get()};
	// prog->run();
	// prog->quit();
	Program::get().run();
	Program::get().quit();
	return EXIT_SUCCESS;
} catch (SDL_exception & err) {
	std::cerr << "Ошибка SDL. Сообщение: " << err.what() << std::endl;
	Program::get().quit();
	return EXIT_FAILURE;
} catch (std::exception & err) {
	std::cerr << "Поймано иное исключение. Сообщение: " << err.what()
		  << std::endl;
	Program::get().quit();
	return EXIT_FAILURE;
} catch (...) {
	std::cerr << "Поймано неизвестное исключение\n";
	Program::get().quit();
	return EXIT_FAILURE;
}
