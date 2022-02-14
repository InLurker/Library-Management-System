#include "Book.h"

void book::addToDatabase() {
	std::string base_path = ("./data/" + ISBN + ".txt");
	std::ofstream textfile;
	std::string line;
	textfile.open(std::filesystem::path(base_path),std::ios::out|std::ios::app);
	if (textfile.is_open()) {
		textfile << title << '\n' << author << '\n' << genre << '\n' << publisher << '\n' << status;
	}
	//indexing files updating
	base_path = "./index_files/";
	textfile.open(std::filesystem::path(base_path + "alphabetical"));
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
