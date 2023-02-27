#pragma once
#include <string>

namespace Log {

	[[noreturn]]
	void Err(std::string message);

	void Warn(std::string message);

}
