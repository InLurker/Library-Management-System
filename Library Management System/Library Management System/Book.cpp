#include "Book.h"

void book::addToDatabase() {
	std::string base_path = ("./data/" + ISBN + ".txt");
	std::fstream textfile;
	std::string line;
	textfile.open(std::filesystem::path(base_path), std::ios::out | std::ios::app);

	//add book details to database
	if (textfile.is_open()) {
		textfile << title << '\n' << author << '\n' << publisher << '\n' << genre << '\n' << status << '\n';
		textfile.close();
	}

	std::string pathnames[4] = {
		"alphabetical/" + std::string(1, toupper(title[0])),
		"author/" + author,
		"genre/" + genre,
		"publisher/" + publisher};

	//update indexing files
	for (int i = 0; i < 4; ++i) {
		base_path = "./index_files/" + pathnames[i] + ".txt";
		std::vector <std::string> entries;
		textfile.open(std::filesystem::path(base_path), std::ios::in);
		bool inserted = false;
		if (textfile.is_open()) {
			while (std::getline(textfile, line)) {
				if (!inserted) {
					if (title <= line) {
						entries.push_back(title);
						entries.push_back(ISBN);
						inserted = true;
					}
				}
				entries.push_back(line);
			}
		}
		textfile.close();

		if (!inserted) { //if data is still not inserted, append at the end of text file
			textfile.open(std::filesystem::path(base_path), std::ios::out | std::ios::app);
			textfile << title << '\n' << ISBN << '\n';
		}
		else {
			textfile.open(std::filesystem::path(base_path), std::ios::out | std::ios::trunc);
			for (const auto& line : entries)
				textfile << line << std::endl;
		}
		textfile.close();
		entries.clear();
	}
}

void book::borrowBook(std::string name, std::string phoneNum) {
}

void book::reserveBook(std::string name, std::string phoneNum) {
}

void book::returnBook() {
}

void book::modifyBorrower(int rowIndex, std::string name, std::string phoneNum) {
}

void book::deleteBorrower(int rowIndex) {
}

void book::modifyDetails(std::string detailType, std::string newDetail) {
}

void book::deleteBook() {
	std::filesystem::remove("./data/" + ISBN + ".txt");

	//delete indexing entries in index_files to be added
}
