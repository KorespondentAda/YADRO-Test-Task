#pragma once

#include <map>
#include <string>
#include <vector>
#include "Cell.hpp"

class Csv {
private:
	std::map<std::string, int> rows;
	std::map<std::string, int> cols;
	std::vector<std::vector<Cell>> table;
	std::istream &source;
	bool readed;
	bool validated;
	int width;

	void InitNames();
	void InitNumbers();
	void InitHeaders();

	void CellParse(Cell &c);
	int FindArg(const std::string &s, int start, int stop);

	int Evaluate(const std::string &s);
	int Operate(char op, int arg1, int arg2);

	bool IsOperation(char c);

public:
	Csv(std::istream &in) : rows(), cols(), table(), source(in), readed(false), validated(false), width(0)
	{}

	void Read();
	void Validate();
	void Write();
};

