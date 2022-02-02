#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "IndexSearching.h"
#include "book_indexing.h"

using namespace std;

void getBookData(string ISBN);

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
                cout << "2. Author" << endl;
                cout << "3. Genre" << endl;
                cout << "4. Publisher" << endl;
                cout << "5. ISBN" << endl;
                cout << "6. Cancel" << endl;
                cout << "Select an option: ";
                cin >> option;

                int selectionNum = 0; //initialized to 0

                string search_query;

                switch (option) {
                case 1: {
                    cout << "\nSearch a title: ";
                    cin.ignore();
                    getline(cin, search_query); //promt user to input search query
                    vector <book_indexing> searchResult = searchByTitle(search_query);

                    if (!searchResult.empty()) {
                        cout << "\nSearch result for \"" + search_query + "\": " << endl;

                        for (book_indexing& book : searchResult) //output search result
                            cout << ++selectionNum << ". " << book.title << endl;

                        if (selectionNum == 1) { //when only 1 title matches query
                            string select;

                            cout << "\nOnly 1 title matches your query." << endl;
                            cout << "Is this the book you're looking for? [Y/N]: ";
                            cin >> select;

                            select = toUpperCase(select);
                            if (select == "Y" || select == "YES") {
                                book_indexing* book_selection = &searchResult.at(0);
                                cout << "Selected title: " << book_selection->title << endl;
                            }
                            else if (select == "N" || select == "NO") {
                                cout << "Book title not selected." << endl;
                            }
                            else {
                                cout << "Not a valid input. Try again." << endl;
                            }
                        }
                        else if (selectionNum > 1) {
                            int select = 0;

                            cout << "Select an entry [1-" + to_string(selectionNum) + "]: ";
                            cin >> select;

                            if (select > 0 && select <= selectionNum) {
                                book_indexing* book_selection = &searchResult.at(select - 1);
                                cout << "Selected title: " << book_selection->title << endl;
                                //getBookDataFromISBN(book_selection->ISBN);
                            }
                            else {
                                cout << "Not a valid input. Try again." << endl;
                            }
                        }
                    }
                    else {
                        cout << "Book title not found." << endl;
                    }
                }
                      break;
                case 2: {
                    cout << "\nSearch an author: ";
                    cin.ignore();
                    getline(cin, search_query); //promt user to input search query
                    vector <string> searchResult = searchIndexFiles("author", search_query);

                    if (!searchResult.empty()) {
                        cout << "\nSearch result for \"" + search_query + "\": " << endl;

                        for (string author : searchResult) {
                            cout << ++selectionNum << ". " << author << endl;
                        }
                        string author;
                        if (selectionNum == 1) { //when only 1 title matches query
                            string select;

                            cout << "\nOnly 1 author matches your query." << endl;
                            cout << "Is this the author you're looking for? [Y/N]: ";
                            cin >> select;

                            select = toUpperCase(select);
                            if (select == "Y" || select == "YES") {
                                author = searchResult.at(0);
                            }
                            else if (select == "N" || select == "NO") {
                                cout << "Author not selected." << endl;
                            }
                            else {
                                cout << "Not a valid input. Try again." << endl;
                            }
                        }
                        else if (selectionNum > 1) {
                            int select = 0;

                            cout << "Select an entry [1-" + to_string(selectionNum) + "]: ";
                            cin >> select;

                            if (select > 0 && select <= selectionNum) {
                                author = searchResult.at(select - 1);
                            }
                            else {
                                cout << "Not a valid input. Try again." << endl;
                            }
                        }

                        if (!author.empty()) {
                            int selectionNum = 0;

                            cout << '\n' << author << "'s books:" << endl;
                            vector <book_indexing> authorBooks = getBookList("author", author);

                            for (book_indexing& book : authorBooks) {
                                cout << ++selectionNum << ". " << book.title << endl;
                            }

                            if (selectionNum == 1) { //when author only has 1 book
                                string select;

                                cout << '\n' << author << " only has 1 book." << endl;
                                cout << "Is this the book you're looking for? [Y/N]: ";
                                cin >> select;

                                select = toUpperCase(select);
                                if (select == "Y" || select == "YES") {
                                    book_indexing* book_selection = &authorBooks.at(0);
                                    cout << "Selected title: " << book_selection->title << endl;
                                    //getBookDataFromISBN(book_selection->ISBN);
                                }
                                else if (select == "N" || select == "NO") {
                                    cout << "Book title not selected." << endl;
                                }
                                else {
                                    cout << "Not a valid input. Try again." << endl;
                                }
                            }
                            else if (selectionNum > 1) {
                                int select = 0;

                                cout << "Select an entry [1-" + to_string(selectionNum) + "]: ";
                                cin >> select;

                                if (select > 0 && select <= selectionNum) {
                                    book_indexing* book_selection = &authorBooks.at(select - 1);
                                    cout << "Selected title: " << book_selection->title << endl;
                                    //getBookDataFromISBN(book_selection->ISBN);
                                }
                                else {
                                    cout << "Not a valid input. Try again." << endl;
                                }
                            }
                        }
                    }
                    else {
                        cout << "Author not found." << endl;
                    }
                }
                      break;
                case 3: {
                    cout << "\nSearch by genre: ";
                    cin.ignore();
                    getline(cin, search_query);
                    vector <string> searchResult = searchIndexFiles("genre", search_query);
                    if (!searchResult.empty()) {
                        cout << "\nSearch result for \"" + search_query + "\": " << endl;
                        for (string genre : searchResult) {
                            cout << ++selectionNum << ". " << genre << endl;
                        }
                        string genre;
                        if (selectionNum == 1) {
                            string select;
                            cout << "Only 1 genre matches your query." << endl;
                            cout << "Is this the genre you're looking for? [Y/N]: ";
                            cin >> select;
                            select = toUpperCase(select);
                            if (select == "Y" || select == "YES") {
                                genre = searchResult.at(0);
                            }
                            else if (select == "N" || select == "NO") {
                                cout << "Genre not selected." << endl;
                            }
                            else {
                                cout << "Not a valid input. Try again." << endl;
                            }
                        }
                        else if (selectionNum > 1) {
                            int select = 0;
                            cout << "Select an entry [1-" + to_string(selectionNum) + "]: ";
                            cin >> select;
                            if (select > 0 && select <= selectionNum) {
                                genre = searchResult.at(select - 1);
                            }
                            else {
                                cout << "Not a valid input. Try again." << endl;
                            }
                        }
                        if (!genre.empty()) {
                            int selectionNum = 0;
                            cout << '\n' << genre <<" books: " << endl;
                            vector <book_indexing> genreBooks = getBookList("genre", genre);
                            for (book_indexing& book : genreBooks) {
                                cout << ++selectionNum << ". " << book.title << endl;
                            }
                            if (selectionNum == 1) {
                                string select;
                                cout << '\n' << "There is only 1 book in the " << genre << " genre." << endl;
                                cout << "Is this the book you're looking for? [Y/N]: ";
                                cin >> select;
                                select = toUpperCase(select);
                                if (select == "Y" || select == "YES") {
                                    book_indexing* book_selection = &genreBooks.at(0);
                                    cout << "Selected title: " << book_selection->title << endl;
                                    //getBookDataFromISBN(book_selection->ISBN); (not yet implemented still in progress)
                                }
                                else if (select == "N" || select == "NO") {
                                    cout << "Book title not selected." << endl;
                                }
                                else {
                                    cout << "Not a valid input. Try again." << endl;
                                }
                            }
                            else if (selectionNum > 1) {
                                int select = 0;

                                cout << "Select an entry [1-" + to_string(selectionNum) + "]: ";
                                cin >> select;

                                if (select > 0 && select <= selectionNum) {
                                    book_indexing* book_selection = &genreBooks.at(select - 1);
                                    cout << "Selected title: " << book_selection->title << endl;
                                    //getBookDataFromISBN(book_selection->ISBN); (not yet implemented still in progress)
                                }
                                else {
                                    cout << "Not a valid input. Try again." << endl;
                                }
                            }
                        }
                    }
                    else {
                        cout << "Genre not found." << endl;
                    }
                }
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

void getBookDataFromISBN(string ISBN) {
    //To be implemented

}
