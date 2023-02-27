#pragma once

#include <map>
#include <string>
#include <vector>
#include "Cell.hpp"

/// CSV-table read-write module
class Csv {
private:
	std::map<std::string, int> rows;         ///< Row number to table row map
	std::map<std::string, int> cols;         ///< Col name to table col map
	std::vector<std::vector<Cell>> table;    ///< Table of CSV cell values
	std::istream &source;                    ///< CSV source stream to read from
	bool readed;                             ///< Is CSV already readed
	bool validated;                          ///< Is CSV already validated
	int width;                               ///< Fields count in every row

	/// Initialize \ref cols map
	void InitNames();

	/// Initialize \ref rows map
	void InitNumbers();

	/// Initialize table maps
	void InitHeaders();

	/// Find out numeric cell value if needed
	void CellParse(Cell &c);

	/// Search string for cell address and retrieve its value
	int FindArg(const std::string &s, int start, int stop);

	/// Evaluate cell expression and return result
	int Evaluate(const std::string &s);

	/// Do expression math operation
	int Operate(char op, int arg1, int arg2);

	/// Check if \a c is supported operation symbol
	///
	/// Currently supproted '+', '-', '*' and '/' symbols.
	bool IsOperation(char c);

public:
	Csv(std::istream &in) : rows(), cols(), table(), source(in), readed(false), validated(false), width(0)
	{}

	/// Read CSV table from \ref source to \ref table
	void Read();

	/// Validate \ref table and fill its cell values
	void Validate();

	/// Write \ref table to stdout
	void Write();
};

