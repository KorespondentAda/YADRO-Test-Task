#pragma once
#include <string>
#include <charconv>

class Parser {
public:
	/// Form substring from given string by start and stop indicies
	///
	/// Wrapper around std::string::substr() method.
	static std::string Substring(std::string s, int from, int to) {
		return s.substr(from, to - from);
	}

	/// Parse given string to int with success check
	///
	/// Wrapper around std::from_chars() method.
	static bool String2Int(std::string s, int &res) {
		auto [ptr, ec] {
			std::from_chars(s.data(), s.data() + s.size(), res)
		};
		return (ec == std::errc() && ptr == s.data() + s.size());
	}

};
