#include "Book.h"

void book::addToDatabase() {
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
