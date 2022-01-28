#include "IndexSearching.h"

std::vector <book_indexing> searchByTitle(std::string query) {
    std::string base_path = (std::filesystem::current_path().string() + "/index_files/alphabetical/");

    std::ifstream indexFile;

    std::vector <book_indexing> searchResult; //vector list container for search results
    std::string line;

    query = toUpperCase(query);

    for (const std::filesystem::directory_entry &textfiles: std::filesystem::directory_iterator(base_path)) { //get all txt files in directory
        indexFile.open(textfiles.path());
        if (indexFile.is_open()) {
            while (std::getline(indexFile, line)) {
                if (!line.empty()) {
                    if (line[0] == '+') {
                        line = line.substr(1, line.size() - 1);

                        if (toUpperCase(line).find(query) != std::string::npos) {//if the query is contained in line

                            book_indexing* entry = new book_indexing;
                            entry->title = line;

                            std::getline(indexFile, line); //get next line

                            if (!line.empty()) {
                                if (line[0] == '-') {
                                    line = line.substr(1, line.size() - 1);
                                    if (is_number(line)) //if line is a number
                                        entry->ISBN = line;
                                }
                            }

                            if (!entry->title.empty() && !entry->ISBN.empty()) {
                                searchResult.push_back(*entry); //add entry to searchResult
                            }
                        }
                    }
                }
            }
        }
    }
    return searchResult; //return vector
}

std::vector<std::string> searchIndexFiles(const std::string searchType, std::string query) {
    std::string base_path = (std::filesystem::current_path().string() + "/index_files/" + searchType + "/");

    std::vector<std::string> searchResult; //vector list container for search results

    query = toUpperCase(query);

    for (const std::filesystem::directory_entry& textfiles : std::filesystem::directory_iterator(base_path)) { //get all txt files in directory
        std::string filename = textfiles.path().filename().string();
        filename = filename.substr(0, filename.size() - 4);
        if(toUpperCase(filename).find(query) != std::string::npos) //if the query is contained in line
            searchResult.push_back(filename); //add to searchResult
    }

    return searchResult;
}

std::vector<std::string> getIndexFiles(const std::string searchType) {
    std::string base_path = (std::filesystem::current_path().string() + "/index_files/" + searchType + "/");

    std::vector<std::string> filename_list; //container for list of filenames

    for (const std::filesystem::directory_entry& textfiles : std::filesystem::directory_iterator(base_path)) { //get all txt files in directory
        std::string filename = textfiles.path().filename().string();
        filename = filename.substr(0, filename.size() - 4);
        filename_list.push_back(filename); //add filenames to list
    }
    return filename_list; //return filename list
}

std::vector<book_indexing> getBookList(const std::string searchType, std::string filename) {
    std::string base_path = (std::filesystem::current_path().string() + "/index_files/" + searchType + "/" + filename + ".txt");

    std::ifstream textfile;
    textfile.open(std::filesystem::path(base_path));

    std::vector <book_indexing> bookList;

    std::string line;
    if (textfile.is_open()) {
        while (std::getline(textfile, line)) {
            if (!line.empty()) {
                if (line[0] == '+') {
                    line = line.substr(1, line.size() - 1);
                    book_indexing* entry = new book_indexing;
                    entry->title = line;

                    std::getline(textfile, line); //get next line

                    if (!line.empty()) {
                        if (line[0] == '-') {
                            line = line.substr(1, line.size() - 1);
                            if (is_number(line)) //if line is a number
                                entry->ISBN = line;
                        }
                    }
                    if (!entry->title.empty() && !entry->ISBN.empty()) {
                        bookList.push_back(*entry); //add entry to searchResult
                    }
                }

            }
        }
    }
    return bookList;
}

std::string toUpperCase(const std::string text) {
    std::string returnString;
    for (char letter : text)
        returnString += toupper(letter);
    return returnString;
}

bool is_number(const std::string str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}