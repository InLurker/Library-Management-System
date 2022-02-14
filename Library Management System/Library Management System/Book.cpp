#include "Book.h"
#include "Data.h"

void book::addToDatabase() {
	std::string base_path = (filesystem::current_path().string() + "/data/" + ISBN + ".txt");
	std::ofstream textfile;
	std::string line;
	textfile.open(filesystem::path(base_path),std::ios::out|std::ios::app);
	if (textfile.is_open()) {
		textfile << title << '\n' << author << '\n' << genre << '\n' << publisher << '\n' << status;
	}
	//indexing files updating to be added
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
