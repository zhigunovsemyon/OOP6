#include "program.h"
#include "sdlexcept.h"

#include <cassert>
#include <iostream>

int main(int, char *[])
try {
	Program::get()();
	return EXIT_SUCCESS;
} catch (SDL_exception const & err) {
	std::cerr << "Ошибка SDL. Сообщение: " << err.what() << std::endl;
	return EXIT_FAILURE;
} catch (TTF_exception const & err) {
	std::cerr << "Ошибка SDL_ttf. Сообщение: " << err.what() << std::endl;
	return EXIT_FAILURE;
} catch (std::exception const & err) {
	std::cerr << "Поймано иное исключение. Сообщение: " << err.what()
		  << std::endl;
	return EXIT_FAILURE;
} catch (...) {
	std::cerr << "Поймано неизвестное исключение\n";
	return EXIT_FAILURE;
}
