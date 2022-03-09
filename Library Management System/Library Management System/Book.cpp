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
	
	std::string pathnames[4] = { //indexing files paths
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
				if (std::getline(textfile, line))
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
			for (const std::string& line : entries)
				textfile << line << std::endl;
		}
		textfile.close();
		entries.clear();
	}
}

void book::borrowBook(const std::string& name, const std::string& phoneNum) {
	status = "Borrowed";
	borrower_record.push_back(name + " - " + phoneNum);

	updateDetails();
}

void book::reserveBook(const std::string& name, const std::string& phoneNum) {
	status = "Reserved";

	reserveName = name + " - " + phoneNum;

	updateDetails();
}

void book::returnBook() {
	if (status == "Borrowed") {
		status = "Available";
	}
	else if (status == "Reserved") {
		status = "Borrowed";
		borrower_record.push_back(reserveName);
		reserveName.clear();
	}
	updateDetails();
}

void book::modifyBorrower(int rowIndex, const std::string& name, const std::string& phoneNum) {
	borrower_record[rowIndex] = (name + " - " + phoneNum);
	updateDetails();
}
void book::deleteBorrower(int rowIndex) {
	borrower_record.erase(borrower_record.begin() + rowIndex);
	updateDetails();
}

void book::modifyDetails(const std::string& detailType, const std::string& newDetail) {
	std::string old_path, new_path;
	std::fstream indexfile;
	std::string line;
	if (detailType == "ISBN" || detailType == "title") { //when detail or isbn, update every index

		//update indexing entries
		std::string pathnames[4] = { //indexing files paths
			"alphabetical/" + std::string(1, toupper(title[0])),
			"author/" + author,
			"genre/" + genre,
			"publisher/" + publisher };

		//when detailType is title, i = 1 to skip alphabetical index updating
		for (int i = (detailType == "title") ? 1 : 0; i < 4; ++i) { //update alphabetical, author, genre, publisher indexing file
			std::string base_path = "./index_files/" + pathnames[i] + ".txt";
			std::vector <std::string> entries;
			indexfile.open(std::filesystem::path(base_path), std::ios::in);
			bool updated = false;

			if (indexfile.is_open()) {
				getline(indexfile, line);
				entries.push_back(line);
				while (std::getline(indexfile, line)) {
					if (!updated) {
						if (ISBN == line) { //when isbn match, remove book from list
							if (detailType == "ISBN") {
								entries.push_back(newDetail); //push new ISBN
							}
							else {
								entries.back() = newDetail; //rename title
								entries.push_back(line);
							}
							updated = true;
							continue;
						}
					}
					entries.push_back(line);
					if (getline(indexfile, line))
						entries.push_back(line);
				}
			}
			indexfile.close();

			indexfile.open(std::filesystem::path(base_path), std::ios::out | std::ios::trunc);

			for (const std::string& line : entries)
				indexfile << line << std::endl;

			indexfile.close();
		}

		if (detailType == "ISBN") {
			std::filesystem::remove("./data/" + ISBN + ".txt");
			ISBN = newDetail;
			updateDetails();
			return;
		}
		else { //title updating doesn't return early
			old_path = "./index_files/alphabetical/" + std::string(1, toupper(title[0])) + ".txt";
			new_path = "./index_files/alphabetical/" + std::string(1, toupper(newDetail[0])) + ".txt";
			title = newDetail;
		}
	}
	else new_path = "./index_files/" + detailType + "/" + newDetail + ".txt";
	
	if (detailType == "author") {
		old_path = "./index_files/author/" + author + ".txt";
		author = newDetail;
	}
	else if (detailType == "publisher") {
		old_path = "./index_files/publisher/" + publisher + ".txt";
		publisher = newDetail;
	}
	else if (detailType == "genre") {
		old_path = "./index_files/genre/" + genre + ".txt";
		genre = newDetail;
	}
	else if (detailType != "title")
		return;


	//remove instance from old indexing file
	indexfile.open(std::filesystem::path(old_path), std::ios::in);
	std::vector <std::string> entries;
	bool removed = false;

	if (indexfile.is_open()) {
		getline(indexfile, line);
		entries.push_back(line);
		while (std::getline(indexfile, line)) {
			if (!removed) {
				if (ISBN == line) { //when isbn match, remove book from list
					entries.pop_back();
					removed = true;
					continue;
				}
			}
			entries.push_back(line);
			if (getline(indexfile, line))
				entries.push_back(line);
		}
	}
	indexfile.close();

	if (entries.empty()) //if vector is empty, remove file
		std::filesystem::remove(old_path);
	else {
		indexfile.open(std::filesystem::path(old_path), std::ios::out | std::ios::trunc);

		for (const std::string& line : entries)
			indexfile << line << std::endl;

		indexfile.close();
	}
	entries.clear();

	//insert to new index file
	indexfile.open(std::filesystem::path(new_path), std::ios::in);
	bool inserted = false;
	if (indexfile.is_open()) {
		while (std::getline(indexfile, line)) {
			if (!inserted) {
				if (title <= line) {
					entries.push_back(title);
					entries.push_back(ISBN);
					inserted = true;
				}
			}
			entries.push_back(line);
			if (std::getline(indexfile, line))
				entries.push_back(line);
		}
	}
	indexfile.close();

	if (!inserted) { //if data is still not inserted, append at the end of text file
		indexfile.open(std::filesystem::path(new_path), std::ios::out | std::ios::app);
		indexfile << title << '\n' << ISBN << '\n';
	}
	else {
		indexfile.open(std::filesystem::path(new_path), std::ios::out | std::ios::trunc);
		for (const std::string& line : entries)
			indexfile << line << std::endl;
	}
	indexfile.close();
	entries.clear();

	updateDetails();
}

void book::deleteBook() {
	//delete entry from database
	std::filesystem::remove("./data/" + ISBN + ".txt");
	
	//delete indexing entries
	std::string pathnames[4] = { //indexing files paths
		"alphabetical/" + std::string(1, toupper(title[0])),
		"author/" + author,
		"genre/" + genre,
		"publisher/" + publisher };

	std::fstream indexfile;
	std::string line;
	for (int i = 0; i < 4; ++i) {
		std::string base_path = "./index_files/" + pathnames[i] + ".txt";
		std::vector <std::string> entries;
		indexfile.open(std::filesystem::path(base_path), std::ios::in);
		bool removed = false;

		if (indexfile.is_open()) {
			getline(indexfile, line);
			entries.push_back(line);
			while (std::getline(indexfile, line)) {
				if (!removed) {
					if (ISBN == line) { //when isbn match, remove book from list
						entries.pop_back();
						removed = true;
						continue;
					}
				}
				entries.push_back(line);
				if (getline(indexfile, line))
					entries.push_back(line);
			}
		}
		indexfile.close();

		if (entries.empty()) //if vector is empty, remove file
			std::filesystem::remove(base_path);
		else {
			indexfile.open(std::filesystem::path(base_path), std::ios::out | std::ios::trunc);

			for (const std::string& line : entries)
				indexfile << line << std::endl;

			indexfile.close();
		}
		entries.clear();
	}

}

void book::updateDetails() {
	std::string base_path = ("./data/" + ISBN + ".txt");
	std::fstream textfile;
	std::string line;
	textfile.open(std::filesystem::path(base_path), std::ios::out | std::ios::trunc);

	//update book details
	if (textfile.is_open()) {
		textfile << title << '\n' << author << '\n' << publisher << '\n' << genre << '\n' << status << '\n';

		//insert borrower's list
		for (const std::string& borrower : borrower_record) {
			textfile << borrower << std::endl;
		}

		if (!reserveName.empty()) {
			textfile << reserveName << std::endl;
		}
	}
	textfile.close();
}
