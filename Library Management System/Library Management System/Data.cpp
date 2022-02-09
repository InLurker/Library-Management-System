#include "Data.h"

book getDataList(string filename) {
	std::string base_path = (filesystem::current_path().string() + "/data/" + filename + ".txt");
	std::ifstream textfile;
	textfile.open(filesystem::path(base_path));
	book returnBook;
	std::string line;
	if (textfile.is_open()) {
		while (getline(textfile, line)) {
			if (!line.empty()) {
				if (line[0] == '+') {
					line = line.substr(1, line.size() - 1);
					book* entry = new book;

					entry->ISBN = filename;

					entry->title = line;
					getline(textfile, line);
					line = line.substr(1, line.size() - 1);
					entry->author = line;
					getline(textfile, line);
					line = line.substr(1, line.size() - 1);
					entry->publisher = line;
					getline(textfile, line);
					line = line.substr(1, line.size() - 1);
					entry->genre = line;
					//borrower's record not yet implemented
					if (!entry->title.empty() && !entry->author.empty() && !entry->publisher.empty() && !entry->genre.empty()) {
						returnBook = *entry;
					}
				}

			}
		}
	}
	return returnBook;
}