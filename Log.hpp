#pragma once
#include <string>

namespace Log {

	[[noreturn]]
	/// Log an error to stderr and exit with bad code
	void Err(std::string message);

	/// Log a warn to stderr
	void Warn(std::string message);

}
