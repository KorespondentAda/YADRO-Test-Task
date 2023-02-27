#pragma once

#include <string>
#include "Log.hpp"

/// Cell of CSV-table
class Cell {
private:
	std::string str;    ///< Origin string representation of cell
	int value;          ///< Value evaluated from string \ref str
	bool hasValue;      ///< Is \ref value already evaluated

public:
	Cell(std::string s) : str(s), value(0), hasValue(false)
	{}

	/// Get origin string representation \ref str of cell
	std::string String() { return str; }

	/// Get evaluated \ref value of cell
	int Value() { return value; }

	/// Check if cell \ref value is valid
	bool HasValue() { return hasValue; }

	/// Set evaluated \ref value of cell
	void SetValue(int v) { hasValue = true; value = v; }

};

