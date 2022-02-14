#include "Data.h"

book getDataList(string filename) {
	std::string base_path = ("./data/" + filename + ".txt");
	std::ifstream textfile;
	textfile.open(filesystem::path(base_path));
	book returnBook;
	std::string line;
	if (textfile.is_open()) {
		getline(textfile, line);
			if (!line.empty()) {
				book* entry = new book;
				entry->ISBN = filename;
				entry->title = line;
				getline(textfile, line); 
				entry->author = line;
				getline(textfile, line);
				entry->publisher = line;
				getline(textfile, line);
				entry->genre = line;
				getline(textfile, line);
				entry->status = line;
				while (getline(textfile, line)) {
					if (line != "\n")
						entry->borrower_record.push_back(line);
				}
				if (!entry->title.empty()&&!entry->author.empty()&&!entry->publisher.empty()&&!entry->genre.empty()) {
					returnBook = *entry;
				}
			}
	}
	return returnBook;
}
