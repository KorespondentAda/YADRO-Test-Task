#include <iostream>
#include <charconv>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

// TODO Error and warning log functions

using Cell = std::string;

// Linear search expression for operator symbol
int findOpIdx(std::string s) {
	for (int i = 1; i < s.size(); i++) {
		// TODO Use map<char, (int)(int,int)>?
		switch(s[i]) {
			case '+':
			case '-':
			case '*':
			case '/':
				return i;
		}
	}
	return -1;
}

// Linear search argument for start index of cell num in given boundaries
int findCellNumIdx(std::string arg, int startIdx, int stopIdx) {
	if (startIdx < 0) {
		std::cerr << "Error [findCellNumIdx]: start index has invalid value " << startIdx << std::endl;
		std::exit(1);
	}
	if (arg.size() < stopIdx) {
		std::cerr << "Error [findCellNumIdx]: stop index " << stopIdx << " bigger than string \"" << arg << "\" size " << arg.size() << "." << std::endl;
		std::exit(1);
	}

	// TODO Do binary search
	// TODO Add string boundary check
	for (int res = startIdx; res <= stopIdx; res++) {
		if (std::isdigit(arg[res]))
			return res;
	}
	return -1;
}

// Convert given string to int number with error check
// TODO If cell start with number but have other symbols?
bool String2Int(std::string s, int &res) {
	return std::from_chars(s.data(), s.data() + s.size(), res).ec == std::errc();
}

int Calculate(std::string s, std::vector<std::vector<Cell>> table, std::map<std::string, int> cols, std::map<int,int> rows) {
	int res;

	if (String2Int(s, res)) {
		return res;

	} else if (s[0] == '=') {
		int opIndex = findOpIdx(s);
		if (opIndex == -1) {
			std::cerr << "Error: no valid operator present in expression." << std::endl;
			std::exit(1);
		}

		int arg1NumIndex = findCellNumIdx(s, 1, opIndex - 1);
		int arg2NumIndex = findCellNumIdx(s, opIndex + 1, s.size() - 1);
		if (arg1NumIndex < 1 || arg1NumIndex >= opIndex) {
			std::cerr << "Error: invalid first argument number in expression " << s << std::endl;
			std::exit(1);
		}
		if (arg2NumIndex <= opIndex || arg2NumIndex >= s.size()) {
			std::cerr << "Error: invalid second argument number in expression " << s << std::endl;
			std::exit(1);
		}

		int arg1Num, arg2Num;
		if (!String2Int(s.substr(arg1NumIndex, opIndex), arg1Num)) {
			std::cerr << "Error: " << s.substr(arg1NumIndex, opIndex - arg1NumIndex) << " is not a number" << std::endl;
			std::exit(1);
		}
		if (!String2Int(s.substr(arg2NumIndex), arg2Num)) {
			std::cerr << "Error: " << s.substr(arg2NumIndex, opIndex - arg2NumIndex) << " is not a number" << std::endl;
			std::exit(1);
		}

		s[arg1NumIndex] = s[arg2NumIndex] = '\0';
		int col1 = cols[s.data() + 1];
		int col2 = cols[s.data() + opIndex + 1];
		int row1 = rows[arg1Num];
		int row2 = rows[arg2Num];
		int arg1 = Calculate(table[row1][col1], table, cols, rows);
		int arg2 = Calculate(table[row2][col2], table, cols, rows);

		switch (s[opIndex]) {
			case '+':
				res = arg1 + arg2;
				break;
			case '-':
				res = arg1 - arg2;
				break;
			case '*':
				res = arg1 * arg2;
				break;
			case '/':
				res = arg1 / arg2;
				break;
			default:
				std::cerr << "Error: No operation specified for operator " << s[opIndex] << std::endl;
				std::exit(1);
		}
		return res;

	} else {
		std::cerr << "Error: Cell is not a number or an expression." << std::endl;
		std::exit(1);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <filename.csv>" << std::endl;
		return 1;
	}

	char *filename = argv[1];

	std::ifstream in(filename);
	if (!in.is_open()) {
		std::cerr << "Error: can't open file \"" << filename << "\"." << std::endl;
		return 1;
	}

	int colCount = 0;
	std::map<std::string, int> cols;
	std::map<int, int> rows;
	std::vector<std::vector<Cell>> table;

	// Read cells to table
	{
	int row = 0, col = 0;
	for (std::string line; std::getline(in, line); row++, col = 0) {
		std::istringstream str(line);
		std::vector<Cell> record;
		for (std::string cell; std::getline(str, cell, ','); col++) {
			record.push_back(cell);
		}
		if (colCount == 0) {
			if (col == 0) {
				std::cerr << "Error: no fields in first (header) record." << std::endl;
				return 1;
			}
			colCount = col;
		}
		if (col != colCount) {
			std::cerr << "Error: invalid number of fields in " << row << " record; got " << col << ", " << colCount << " expected." << std::endl;
			return 1;
		}
		table.push_back(record);
	}
	}

	if (table.empty()) {
		std::cerr << "Error: file \"" << filename << "\" empty" << std::endl;
		return 1;
	}

	// Read table headers and row numbers
	if (!table[0][0].empty()) {
		std::cerr << "Warning: corner header field is non-empty; ignoring." << std::endl;
	}
	for (int i = 1; i < table[0].size(); i++) {
		if (table[0][i].empty()) {
			std::cerr << "Error: column " << i << " header is empty." << std::endl;
			return 1;
		}
		cols.insert({table[0][i], i});
	}
	for (int i = 1; i < table.size(); i++) {
		int rowNum;
		std::string str = table[i][0];
		auto [ptr, ec] { std::from_chars(str.data(), str.data() + str.size(), rowNum) };
		if (ec != std::errc()) {
			std::cerr << "Error: row " << i << " number is invalid." << std::endl;
			return 1;
		}
		rows.insert({rowNum, i});
	}

	// Write result table
	for (int i = 0; i < table[0].size(); i++) {
		if (i != 0) std::cout << ',';
		std::cout << table[0][i];
	}
	for (int i = 1; i < table.size(); i++) {
		std::cout << std::endl;
		for (int j = 0; j < table[i].size(); j++) {
			if (j != 0) std::cout << ',';
			std::cout << Calculate(table[i][j], table, cols, rows);
		}
	}
	std::cout << std::endl;

	return 0;
}

