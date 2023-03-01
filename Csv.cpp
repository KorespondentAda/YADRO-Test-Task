#include <string>
#include <sstream>
#include <iostream>
#include "Csv.hpp"
#include "Parser.hpp"

void Csv::CheckName(std::string name) {
	if (FindOp(name) >= 0) {
		Log::Err("Column name can't contain operation symbol");
	}
}

void Csv::CheckNumber(int num) {
	if (num <= 0) {
		Log::Err("Row number must be positive");
	}
}

void Csv::InitNames() {
	for (int i = 0; i < table[0].size(); i++) {
		CheckName(table[0][i].String());
		cols.insert({table[0][i].String(), i});
	}
}

void Csv::InitNumbers() {
	for (int i = 1; i < table.size(); i++) {
		int num;
		if (Parser::String2Int(table[i][0].String(), num)) {
			CheckNumber(num);
			rows.insert({table[i][0].String(), i});
			table[i][0].SetValue(num);
		} else {
			Log::Err("Row number is not a valid number");
		}
	}
}

void Csv::InitHeaders() {
	InitNames();
	InitNumbers();
}

int Csv::FindOp(const std::string &s) {
	for (int i = 1; i < s.size(); i++) {
		if (IsOperation(s[i]))
			return i;
	}
	return -1;
}

int Csv::FindArg(const std::string &s, int start, int stop) {
	if (start >= stop) {
		Log::Err("Invalid argument: its start must be lesser than stop");
	}

	int res;
	if (Parser::String2Int(Parser::Substring(s, start, stop), res)) {
		return res;
	}

	int div;
	for (div = start; div < stop && !std::isdigit(s[div]); div++);
	if (div == start || div == stop) {
		std::cout << s << std::endl;
		Log::Err("Invalid argument: no cell name or number present");
	}
	if (rows.count(Parser::Substring(s, div, stop)) == 0 || cols.count(Parser::Substring(s, start, div)) == 0) {
		Log::Err("Invalid argument: unexpected cell name or number found");
	}
	int row = rows[Parser::Substring(s, div, stop)];
	int col = cols[Parser::Substring(s, start, div)];
	CellParse(table[row][col]);
	return table[row][col].Value();
}

int Csv::Evaluate(const std::string &s) {
	int opIndex = FindOp(s);
	if (opIndex < 0) {
		Log::Err("Expression have no operation symbols");
	}

	int arg1 = FindArg(s, 1, i);
	int arg2 = FindArg(s, i+1, s.size() + 1);
	return Operate(s[i], arg1, arg2);
}

void Csv::CellParse(Cell &c) {
	int num;
	if (c.HasValue()) {
		return;
	} else if (Parser::String2Int(c.String(), num)) {
		c.SetValue(num);
	} else if (c.String()[0] == '=') {
		c.SetValue(Evaluate(c.String()));
	} else {
		Log::Err("Invalid cell value");
	}
}

bool Csv::IsOperation(char c) {
	switch(c) {
		case '+':
		case '-':
		case '*':
		case '/':
			return true;
	}
	return false;
}

int Csv::Operate(char op, int arg1, int arg2) {
	switch (op) {
		case '+':
			if ((long long)arg1 + (long long)arg2 > INT32_MAX ||
				(long long)arg1 + (long long)arg2 < INT32_MIN)
				Log::Err("Invalid operation: variable overflow");
			return arg1 + arg2;
		case '-':
			if ((long long)arg1 + (long long)arg2 > INT32_MAX ||
				(long long)arg1 + (long long)arg2 < INT32_MIN)
				Log::Err("Invalid operation: variable overflow");
			return arg1 - arg2;
		case '*':
			if ((long long)arg1 * (long long)arg2 > INT32_MAX ||
				(long long)arg1 * (long long)arg2 < INT32_MIN)
				Log::Err("Invalid operation: variable overflow");
			return arg1 * arg2;
		case '/':
			if (arg2 == 0)
				Log::Err("Invalid operation: dividing by zero");
			return arg1 / arg2;
		default:
			Log::Err("Invalid operation symbol");
	}
}


void Csv::Read() {
	for (std::string line; std::getline(source, line); ) {
		std::istringstream ss(line);
		std::vector<Cell> row;
		for (std::string cell; std::getline(ss, cell, ','); ) {
			row.push_back(cell);
		}

		if (width == 0)
			width = row.size();
		if (row.size() != width) {
			Log::Err("Invalid number of fields in record");
		}

		table.push_back(row);
	}

	if (width == 0) {
		Log::Err("Empty CSV");
	}

	InitHeaders();
}

void Csv::Validate() {
	if (!readed)
		Read();

	for (int i = 1; i < table.size(); i++)
		for (int j = 1; j < width; j++)
			CellParse(table[i][j]);
}

void Csv::Write() {
	if (!validated)
		Validate();

	std::cout << table[0][0].String();
	for (int i = 1; i < width; i++) {
		std::cout << ',' << table[0][i].String();
	}
	for (int i = 1; i < table.size(); i++) {
		std::cout << std::endl << table[i][0].Value();
		for (int j = 1; j < width; j++) {
			std::cout << ',' << table[i][j].Value();
		}
	}
	std::cout << std::endl;
}

