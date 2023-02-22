#include <iostream>
#include <charconv>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

// TODO Don't need, use just string?
class Cell {
private:
	int value;
	std::string str; // TODO Rename?
	bool calculated;

public:
	Cell(std::string s) : str(s)
	{}

	bool isCalculated() { return calculated; }
	std::string getString() { return str; }
	int getValue() { return value; }
	void Calculate() {
	}
};

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
	int row = 0, col = 0;
	std::map<std::string, int> cols;
	std::map<int, int> rows;
	std::vector<std::vector<Cell>> table;

	// Read cells to table
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

	if (table.empty()) {
		std::cerr << "Error: file \"" << filename << "\" empty" << std::endl;
		return 1;
	}

	// Read table headers and row numbers
	if (!table[0][0].getString().empty()) {
		std::cerr << "Warning: corner header field is non-empty; ignoring." << std::endl;
	}
	for (int i = 1; i < table[0].size(); i++) {
		if (table[0][i].getString().empty()) {
			std::cerr << "Error: column " << i << " header is empty." << std::endl;
			return 1;
		}
		cols.insert({table[0][i].getString(), i});
	}
	for (int i = 1; i < table.size(); i++) {
		int rowNum;
		std::string str = table[i][0].getString();
		auto [ptr, ec] { std::from_chars(str.data(), str.data() + str.size(), rowNum) };
		if (ec != std::errc()) {
			std::cerr << "Error: row " << i << " number is invalid." << std::endl;
			return 1;
		}
		rows.insert({rowNum, i});
	}

	// Write result table
	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[i].size(); j++) {
			if (j != 0) std::cout << ',';
			std::cout << table[i][j].getString();
		}
		std::cout << std::endl;
	}

	return 0;
}

