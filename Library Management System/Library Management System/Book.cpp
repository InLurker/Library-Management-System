#include "Book.h"
#include "Data.h"
#pragma warning(disable:4996)
void book::addToDatabase(std::string filename) {
	std::string base_path = (filesystem::current_path().string() + "/data/" + filename + ".txt");
	std::ofstream textfile;
	std::string line;
	textfile.open(filesystem::path(base_path),std::ios::out|std::ios::app);
	if (textfile.fail()) {
		throw std::ios_base::failure(strerror(errno));
	}
	textfile.exceptions(textfile.exceptions() | std::ios::failbit | std::ifstream::badbit);
	book* entry = new book;
	entry->ISBN = filename;//where the issues start
	//push book data into text files, not yet implemented
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
