#include <fstream>
#include "Csv.hpp"
#include "Log.hpp"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		Log::Err("Usage: csvreader <filename.csv>");
	}

	std::string filename(argv[1]);

	std::ifstream in(filename);
	if (!in.is_open()) {
		Log::Err("Error: can't open file");
	}

	Csv file(in);
	file.Write();

	return 0;
}

