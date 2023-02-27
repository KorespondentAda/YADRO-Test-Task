#pragma once
#include <string>
#include <charconv>

class Parser {
public:
	static std::string Substring(std::string s, int from, int to) {
		return s.substr(from, to - from);
	}

	static bool String2Int(std::string s, int &res) {
		auto [ptr, ec] {
			std::from_chars(s.data(), s.data() + s.size(), res)
		};
		//std::cout << "String2Int: \"" << s << "\" converted to " << res << " with ptr: " << ptr - s.data() << " while end is " << s.size() << std::endl;
		return (ec == std::errc() && ptr == s.data() + s.size());
	}

};
