#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "book_indexing.h"

using namespace std;

vector <book_indexing> searchByTitle(string query); //forward declarations

int main() {
    //initial setup
    filesystem::create_directories("./data");
    filesystem::create_directories("./index_files/alphabetical");
    filesystem::create_directories("./index_files/publisher");
    filesystem::create_directories("./index_files/author");
    filesystem::create_directories("./index_files/genre");

    cout << "===================================================" << endl;
    cout << "              Welcome To Our Library!              " << endl;
    cout << "===================================================" << endl;

    bool loop = true;

    while (loop) {
        int action;

        cout << "\nWhat can we help you with?" << endl;
        cout << "1. Search a book" << endl;
        cout << "2. Insert a new book" << endl;
        cout << "3. Return a book" << endl;
        cout << "4. Borrow a book" << endl;
        cout << "5. Reserve a book" << endl;
        cout << "Select an action: ";
        cin >> action;

        int option = 0; // initialized to 0

        switch (action) {
        case 1:
            while (option != 6) {
                cout << "\nSearch book by:" << endl;
                cout << "1. Title" << endl;
                cout << "2. Publisher" << endl;
                cout << "3. Author" << endl;
                cout << "4. Genre" << endl;
                cout << "5. ISBN" << endl;
                cout << "6. Cancel" << endl;
                cout << "Select an option: ";
                cin >> option;

                int selectionNum = 0; //initialized to 0

                switch (option) {
                case 1: {
                    cout << "\nSearch a title: ";
                    string search_query;
                    cin.ignore();
                    getline(cin, search_query); //promt user to input search query
                    vector <book_indexing> searchResult = searchByTitle(search_query);

                    if (!searchResult.empty()) {
                        cout << "\nSearch result for \"" + search_query + "\": " << endl;

                        for (book_indexing entry : searchResult)
                            cout << ++selectionNum << ". " << entry.title << endl;
                        
                        if (selectionNum == 1) {
                            int select = 0;
                            cout << "This is the only title available. \nEnter 1 to confirm this search. If not, enter an integer other than 1: ";
                            cin >> select;
                            book_indexing* selection = &searchResult.at(selectionNum - 1);
                            switch (select) {
                            case 1:
                                cout << "Selected title: " << selection->title << endl;
                                break;
                            default:
                                cout<< "Book title not selected." << endl;
                                break;
                            }
                        }else if (selectionNum > 1) {
                            int select = 0;
                            cout << "Select an entry [1-" + to_string(selectionNum) + "]: ";
                            cin >> select;
                            if (select > selectionNum || select < 1) {
                                cout << "Not a valid input. Try again." << endl;
                                break;
                            }
                            book_indexing* selection = &searchResult.at(select - 1);
                            if(select<=selectionNum) {
                                cout << "Selected title: " << selection->title << endl;
                            }
                        }
                        else {
                            cout << "Book title not found." << endl;
                        }
                        
                        //for future implementation: user's numerical (title) input that gets mistaken as ISBN when outputted
                    }
                    else {
                        cout << "Book title not found." << endl;
                    }
                    break;
                }
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                default:
                    cout << "Invalid input!" << endl;
                }
            }
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            return 0;
            break;
        default:
            cout << "Invalid input!" << endl;
        }

    }


}

//DISCLAIMER searchByTitle is not tested yet!
vector <book_indexing> searchByTitle(string query) {
    string base_path = (filesystem::current_path().string() + "/index_files/alphabetical/");
    char index_filename = 'A';

    ifstream indexFile;

    vector <book_indexing> searchResult; //vector list container for search results
    string line;

    while (index_filename <= 'Z') { //loop until reach Z.txt
        indexFile.open(filesystem::path (base_path + index_filename++ + ".txt"));
        if (indexFile.is_open()) {
            while (getline(indexFile, line)) {
                if (line.length() > 0) {
                    if (line.find(query) != string::npos) { //if the query is contained in a line
                        book_indexing* entry = new book_indexing;
                        entry->title = line;
                        getline(indexFile, entry->ISBN);
                        searchResult.push_back(*entry); //insert entry to searchResult list
                    }
                }
            }
        }
    }
    return searchResult; //return vector
}
