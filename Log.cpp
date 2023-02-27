#include <string>
#include <iostream>
#include "Log.hpp"

namespace Log {

[[noreturn]]
void Err(std::string message) {
	std::cerr << "Error: " << message << std::endl;
	std::exit(1);
}

void Warn(std::string message) {
	std::cerr << "Warning: " << message << std::endl;
}

}
