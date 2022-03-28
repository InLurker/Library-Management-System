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

	//create book_indexing object for new entry
	book_indexing* newEntry = new book_indexing;
	newEntry->title = title;
	newEntry->ISBN = ISBN;

	//retrieve indexing files
	for (int i = 0; i < 4; ++i) {
		base_path = "./index_files/" + pathnames[i] + ".txt";
		std::vector <book_indexing> entries;
		textfile.open(std::filesystem::path(base_path), std::ios::in);
		if (textfile.is_open()) {
			book_indexing* entry = new book_indexing;
			while (std::getline(textfile, line)) {
				entry->title = line;
				getline(textfile, line);
				entry->ISBN = line;
				entries.push_back(*entry); //add existing book indexes to vector
			}
			delete entry; //deallocate memory
		}
		textfile.close();

		//perform binary search + insertion to insert new entry to vector array
		int index = binarySearchPosition(entries, newEntry);
		entries.insert(entries.begin() + index, *newEntry);
		
		textfile.open(std::filesystem::path(base_path), std::ios::out | std::ios::trunc);
		for (const book_indexing& entry : entries)
			textfile << entry.title << std::endl << entry.ISBN << std::endl;

		textfile.close();
		entries.clear();
	}
	delete newEntry; //prevent memory leak
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

	//create book_indexing object for old and new entry
	book_indexing* oldEntry = new book_indexing;
	oldEntry->title = title;
	oldEntry->ISBN = ISBN;

	book_indexing* newEntry = new book_indexing;
	newEntry->title = (detailType == "title") ? newDetail : title;
	newEntry->ISBN = (detailType == "ISBN") ? newDetail : ISBN;

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
			std::vector <book_indexing> entries;
			indexfile.open(std::filesystem::path(base_path), std::ios::in);
			bool updated = false;

			if (indexfile.is_open()) {
				book_indexing* entry = new book_indexing;
				while (std::getline(indexfile, line)) {
					entry->title = line;
					getline(indexfile, line);
					entry->ISBN = line;
					entries.push_back(*entry); //add existing book indexes to vector
				}
				delete entry; //deallocate memory
			}
			indexfile.close();


			int index = binarySearchPosition(entries, oldEntry);
			if (detailType == "ISBN") {
				entries.at(index).ISBN = newDetail; //replace ISBN
			}
			else {
				entries.erase(entries.begin() + index); //remove oldEntry from vector

				index = binarySearchPosition(entries, newEntry);
				entries.insert(entries.begin() + index, *newEntry); //insert entry with new title
			}

			indexfile.open(std::filesystem::path(base_path), std::ios::out | std::ios::trunc);

			for (const book_indexing& entry : entries)
				indexfile << entry.title << std::endl << entry.ISBN << std::endl;

			indexfile.close();
			entries.clear();
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
	std::vector <book_indexing> entries;

	if (indexfile.is_open()) {
		while (std::getline(indexfile, line)) {
			book_indexing* entry = new book_indexing;
			entry->title = line;
			getline(indexfile, line);
			entry->ISBN = line;
			entries.push_back(*entry); //add existing book indexes to vector
			delete entry; //deallocate memory
		}
	}
	indexfile.close();

	int index = binarySearchPosition(entries, oldEntry);
	entries.erase(entries.begin() + index);

	if (entries.empty()) //if vector is empty, remove file
		std::filesystem::remove(old_path);
	else {
		indexfile.open(std::filesystem::path(old_path), std::ios::out | std::ios::trunc);
		for (const book_indexing& entry : entries)
			indexfile << entry.title << std::endl << entry.ISBN << std::endl;
		indexfile.close();
	}
	entries.clear();

	//insert to new index file
	if (indexfile.is_open()) {
		book_indexing* entry = new book_indexing;
		while (std::getline(indexfile, line)) {
			entry->title = line;
			getline(indexfile, line);
			entry->ISBN = line;
			entries.push_back(*entry); //add existing book indexes to vector
		}
		delete entry; //deallocate memory
	}
	indexfile.close();

	index = binarySearchPosition(entries, newEntry);
	entries.insert(entries.begin() + index, *newEntry);

	indexfile.open(std::filesystem::path(new_path), std::ios::out | std::ios::trunc);
	for (const book_indexing& entry : entries)
		indexfile << entry.title << std::endl << entry.ISBN << std::endl;
	indexfile.close();
	entries.clear();

	//prevent memory leak
	delete oldEntry;
	delete newEntry;

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

	book_indexing* toDelete = new book_indexing;
	toDelete->ISBN = ISBN;
	toDelete->title = title;

	std::fstream indexfile;
	std::string line;
	for (int i = 0; i < 4; ++i) {
		std::string base_path = "./index_files/" + pathnames[i] + ".txt";
		std::vector <book_indexing> entries;
		indexfile.open(std::filesystem::path(base_path), std::ios::in);

		if (indexfile.is_open()) {
			book_indexing* entry = new book_indexing;
			while (std::getline(indexfile, line)) {
				entry->title = line;
				getline(indexfile, line);
				entry->ISBN = line;
				entries.push_back(*entry); //add existing book indexes to vector
			}
			delete entry; //deallocate memory
		}
		indexfile.close();

		int index = binarySearchPosition(entries, toDelete);
		entries.erase(entries.begin() + index);

		if (entries.empty()) //if vector is empty, remove file
			std::filesystem::remove(base_path);
		else {
			indexfile.open(std::filesystem::path(base_path), std::ios::out | std::ios::trunc);
			for (const book_indexing& entry : entries)
				indexfile << entry.title << std::endl << entry.ISBN << std::endl;
			indexfile.close();
		}
		entries.clear();
	}
	delete toDelete;
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

int book::binarySearchPosition(const std::vector<book_indexing>& vectorArray, const book_indexing* newEntry) const {
	//computes position retrieved when binary search is performed on an array
	int left = 0;
	int right = vectorArray.size() - 1;
	int mid;

	//divide and conquer
	while (left <= right) {
		mid = left + (right - left) / 2;
		if (newEntry->title == vectorArray[mid].title && newEntry->ISBN == vectorArray[mid].ISBN)
			return mid;
		else if (newEntry->title > vectorArray[mid].title)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return left;
}
