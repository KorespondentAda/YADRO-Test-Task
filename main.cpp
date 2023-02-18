#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

class Cell {
private:
	int value;
	std::string str; // TODO Rename?
	bool calculated;

public:
	Cell(std::string s) : str(s)
	{}

	bool isNeedToCalculate() { return !calculated; }
	std::string getString() { return str; }
	int getValue() { return value; }
	void Calculate() {
	}
};

int main(int argc, char *argv[]) {
	// TODO Get filename from argv
	std::ifstream in("../file.csv");
	// TODO Error: file does not open

	int colCount = 0;
	int row = 0, col = 0;
	std::map<std::string, int> cols;
	std::map<std::string, int> rows;
	std::vector<std::vector<Cell>> table;

	// Read cells to table
	// TODO Maybe read all cells to table, then just throw names to maps?
	for (std::string line; std::getline(in, line); row++, col = 0) {
		// TODO Error while reading?
		std::istringstream str(line);
		std::vector<Cell> record;
		for (std::string cell; std::getline(str, cell, ','); col++) {
			// XXX
			//std::cout << "Cell " << row << ':' << col << ": " << cell << std::endl;
			record.push_back(cell);
		}
		if (colCount == 0) {
			if (col == 0) {
				// TODO Error: no header fields
			}
			colCount = col;
		}
		if (col != colCount) {
			// TODO Error: invalid count of fields in record
		}
		table.push_back(record);
	}

	// Read table headers
	for (int i = 0; i < table.size(); i++) {
		rows.insert({table[i][0].getString(), i});
	}
	for (int i = 0; i < table[0].size(); i++) {
		cols.insert({table[0][i].getString(), i});
	}

	/*
	// XXX Check name mappings
	std::cout << std::endl << "Col names:" << std::endl;
	for (auto head : cols) {
		std::cout << head.first << " -> " << head.second << std::endl;
	}
	std::cout << std::endl << "Row names:" << std::endl;
	for (auto head : rows) {
		std::cout << head.first << " -> " << head.second << std::endl;
	}
	*/

	// XXX
	//std::cout << std::endl << "Result table:" << std::endl;
	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[i].size(); j++) {
			if (j != 0) std::cout << ',';
			std::cout << table[i][j].getString();
		}
		std::cout << std::endl;
	}

	return 0;
}

