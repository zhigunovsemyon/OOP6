#include "program.h"
#include <print>

int main(int, char *[])
try {
	Program::get()();
	return EXIT_SUCCESS;
} catch (std::exception const & err) {
	std::println(stderr, "Ошибка с сообщением: {}", err.what());
	return EXIT_FAILURE;
} catch (...) {
	std::println(stderr, "Неизветная ошибка");
	return EXIT_FAILURE;
}
