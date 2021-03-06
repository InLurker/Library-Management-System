#include "IndexSearching.h"

std::vector <book_indexing> searchByTitle(std::string query) {
    std::string base_path = "./index_files/alphabetical/";

    std::ifstream indexFile;

    std::vector <book_indexing> searchResult; //vector list container for search results
    std::string line;

    query = toUpperCase(query);

    for (const std::filesystem::directory_entry &textfiles: std::filesystem::directory_iterator(base_path)) { //get all txt files in directory
        indexFile.open(textfiles.path(), std::ifstream::in);
        if (indexFile.is_open()) {
            book_indexing* entry = new book_indexing;
            while (std::getline(indexFile, line)) {
                if (!line.empty()) {
                    if (toUpperCase(line).find(query) != std::string::npos) {//if the query is contained in line
                        entry->title = line;
                        std::getline(indexFile, line); //get next line
                        if (!line.empty()) {
                            entry->ISBN = line;
                            searchResult.push_back(*entry); //add entry to searchResult
                        }
                    }
                    else {
                        indexFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
            }
            delete entry; //prevent memory leak
        }
        indexFile.close();
    }
    return searchResult; //return vector
}

std::vector<std::string> searchIndexFiles(const std::string& searchType, std::string query) {
    std::string base_path = "./index_files/" + searchType + "/";

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

std::vector<std::string> getIndexFiles(const std::string& searchType) {
    std::string base_path = ("./index_files/" + searchType + "/");

    std::vector<std::string> filename_list; //container for list of filenames

    for (const std::filesystem::directory_entry& textfiles : std::filesystem::directory_iterator(base_path)) { //get all txt files in directory
        std::string filename = textfiles.path().filename().string();
        filename = filename.substr(0, filename.size() - 4);
        filename_list.push_back(filename); //add filenames to list
    }
    return filename_list; //return filename list
}

std::vector<book_indexing> getBookList(const std::string& searchType, const std::string& filename) {
    std::string base_path = "./index_files/" + searchType + "/" + filename + ".txt";

    std::ifstream textfile;
    textfile.open(std::filesystem::path(base_path), std::ifstream::in);

    std::vector <book_indexing> bookList;

    std::string line;
    if (textfile.is_open()) {
        book_indexing* entry = new book_indexing;
        while (std::getline(textfile, line)) {
            if (!line.empty()) {
                entry->title = line;
                std::getline(textfile, line); //get next line
                if (!line.empty()) {
                    entry->ISBN = line;
                    bookList.push_back(*entry); //add entry to searchResult
                }
            }
        }
        delete entry; //prevent memory leak
    }
    textfile.close();
    return bookList;
}

std::string toUpperCase(const std::string text) {
    std::string returnString;
    for (char letter : text)
        returnString += toupper(letter);
    return returnString;
}