#pragma once

#include <charconv>
#include <map>
#include <string>
#include "Log.hpp"

class Cell {
private:
	std::string str;
	int value;
	bool hasValue;

public:
	Cell(std::string s) : str(s), value(0), hasValue(false)
	{}

	std::string String() { return str; }
	int Value() { return value; }
	bool HasValue() { return hasValue; }
	void SetValue(int v) { value = v; }

};

