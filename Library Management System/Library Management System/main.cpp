#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "IndexSearching.h"
#include "book_indexing.h"
#include "Data.h"
#include "Book.h"

using namespace std;

void printBookData(const book &Book);
string number_clear_formatting(const string& text);
bool is_number(const string& str);

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
        cout << "6. Adminstrator mode" << endl;
        cout << "7. Exit" << endl;
        cout << "Select an action: ";
        cin >> action;

        

        switch (action) {
        case 1: {
            int option = 0;
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
                book BookData;

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
                                BookData = getDataList(book_selection->ISBN);
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
                                BookData = getDataList(book_selection->ISBN);
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
                                    BookData = getDataList(book_selection->ISBN);
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
                                    BookData = getDataList(book_selection->ISBN);
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
                    vector <string> genreList = getIndexFiles("genre");
                    string genre;

                    if (!genreList.empty()) {
                        if (genreList.size() == 1) { //when only 1 title matches query
                            string select;

                            cout << "\nOnly 1 genre available." << endl;
                            cout << "Is this the genre you're looking for? [Y/N]: ";
                            cin >> select;

                            select = toUpperCase(select);
                            if (select == "Y" || select == "YES") {
                                genre = genreList.at(0);
                            }
                            else if (select == "N" || select == "NO") {
                                cout << "Genre not selected." << endl;
                            }
                            else {
                                cout << "Not a valid input. Try again." << endl;
                            }
                        }
                        else if (genreList.size() > 1) {

                            cout << "\nList of available genres: " << endl;

                            for (string genreEntries : genreList) {
                                cout << ++selectionNum << ". " << genreEntries << endl;
                            }

                            int select = 0;
                            cout << "Select a genre [1-" + to_string(selectionNum) + "]: ";
                            cin >> select;

                            if (select > 0 && select <= selectionNum) {
                                genre = genreList.at(select - 1);
                            }
                            else {
                                cout << "Not a valid input. Try again." << endl;
                            }
                        }

                        if (!genre.empty()) {
                            int selectionNum = 0;

                            cout << '\n' << "Books under " << '\"' << genre << '\"' << " genre:" << endl;
                            vector <book_indexing> genreBooks = getBookList("genre", genre);

                            for (book_indexing& book : genreBooks) {
                                cout << ++selectionNum << ". " << book.title << endl;
                            }

                            if (selectionNum == 1) { //when author only has 1 book
                                string select;

                                cout << '\n' << "Genre \"" << genre << "\" only has 1 book." << endl;
                                cout << "Is this the book you're looking for? [Y/N]: ";
                                cin >> select;

                                select = toUpperCase(select);
                                if (select == "Y" || select == "YES") {
                                    book_indexing* book_selection = &genreBooks.at(0);
                                    BookData = getDataList(book_selection->ISBN);
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
                                    BookData = getDataList(book_selection->ISBN);
                                }
                                else {
                                    cout << "Not a valid input. Try again." << endl;
                                }
                            }
                        }
                    }
                    else {
                        cout << "No genre available." << endl;
                    }
                }
                      break;
                case 4: {
                    cout << "\nSearch by publisher: ";
                    cin.ignore();
                    getline(cin, search_query);
                    vector <string> searchResult = searchIndexFiles("publisher", search_query);
                    if (!searchResult.empty()) {
                        cout << "\nSearch result for \"" + search_query + "\": " << endl;
                        for (string publisher : searchResult) {
                            cout << ++selectionNum << ". " << publisher << endl;
                        }
                        string publisher;
                        if (selectionNum == 1) {
                            string select;
                            cout << "Only 1 publisher matches your query." << endl;
                            cout << "Is this the publisher you're looking for? [Y/N]: ";
                            cin >> select;
                            select = toUpperCase(select);
                            if (select == "Y" || select == "YES") {
                                publisher = searchResult.at(0);
                            }
                            else if (select == "N" || select == "NO") {
                                cout << "Publisher not selected." << endl;
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
                                publisher = searchResult.at(select - 1);
                            }
                            else {
                                cout << "Not a valid input. Try again." << endl;
                            }
                        }
                        if (!publisher.empty()) {
                            int selectionNum = 0;
                            cout << '\n' << publisher << "'s books:" << endl;
                            vector <book_indexing> publisherBooks = getBookList("publisher", publisher);
                            for (book_indexing& book : publisherBooks) {
                                cout << ++selectionNum << ". " << book.title << endl;
                            }
                            if (selectionNum == 1) {
                                string select;
                                cout << '\n' << "Only 1 book published by " << publisher << "." << endl;
                                cout << "Is this the book you're looking for? [Y/N]: ";
                                cin >> select;
                                select = toUpperCase(select);
                                if (select == "Y" || select == "YES") {
                                    book_indexing* book_selection = &publisherBooks.at(0);
                                    BookData = getDataList(book_selection->ISBN);
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
                                    book_indexing* book_selection = &publisherBooks.at(select - 1);
                                    BookData = getDataList(book_selection->ISBN);
                                }
                                else {
                                    cout << "Not a valid input. Try again." << endl;
                                }
                            }
                        }
                    }
                    else {
                        cout << "Publisher not found." << endl;
                    }
                }
                      break;
                case 5: {
                    cout << "Input ISBN number: ";
                    cin.ignore();
                    getline(cin, search_query);
                    if (!search_query.empty()) {
                        search_query = number_clear_formatting(search_query);
                        if (is_number(search_query)) {
                            BookData = getDataList(search_query);
                            if (BookData.title.empty()) {
                                cout << "Book doesn't exist in our database." << endl;
                            }
                        }
                        else cout << "Not a valid ISBN number." << endl;
                    }
                }
                      break;
                case 6:
                    break;
                default:
                    cout << "Invalid input!" << endl;
                }
                if (!BookData.title.empty()) {
                    cout << '\n';
                    printBookData(BookData);
                }
            }
        }
            break;
        case 2: {
            string bookDetails;
            cout << "\nEnter book details." << endl;
            cout << "ISBN: ";
            cin.ignore();
            getline(cin, bookDetails);
            bookDetails = number_clear_formatting(bookDetails);
            if (is_number(bookDetails)) {
                if (filesystem::exists("./data/" + bookDetails + ".txt")) { //if txt file of the same ISBN exist in database
                    cout << "Book already existed." << endl;
                    string select;
                    cout << "Override previous entry?[Y/N]: ";
                    cin >> select;
                    select = toUpperCase(select);
                    if (select == "Y" || select == "YES") {
                        if (filesystem::remove("./data/" + bookDetails + ".txt"))
                            cout << "Insert new details." << endl;
                    }
                    else if (select == "N" || select == "NO") {
                        cout << "Book not inserted." << endl;
                        break;
                    }
                    else {
                        cout << "Not a valid input. Try again." << endl;
                        break;
                    }
                    cin.ignore();
                }
                book newBook;
                newBook.ISBN = bookDetails;

                cout << "Title: ";
                getline(cin, bookDetails);
                newBook.title = bookDetails;

                cout << "Author: ";
                getline(cin, bookDetails);
                newBook.author = bookDetails;

                cout << "Genre: ";
                getline(cin, bookDetails);
                newBook.genre = bookDetails;

                cout << "Publisher: ";
                getline(cin, bookDetails);
                newBook.publisher = bookDetails;

                newBook.status = "Available";

                newBook.addToDatabase();

                if (filesystem::exists("./data/" + newBook.ISBN + ".txt")) {
                    cout << "Book successfully inserted." << endl;
                }
            }
            else {
                cout << "Not a valid ISBN number." << endl;
            }
        }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6: {
            int option = 0;
            while (option != 7) {
                cout << "\nAdministrator Mode:" << endl;
                cout << "1. Insert a book" << endl;
                cout << "2. Modify a book" << endl;
                cout << "3. Delete a book" << endl;
                cout << "4. Modify a borrower" << endl;
                cout << "5. Delete a borrower" << endl;
                cout << "6. Search a borrowing list" << endl;
                cout << "7. Exit Administrator Mode" << endl;
                cout << "Select an option: ";
                cin >> option;

                switch (option) {
                case 1: {
                    string bookDetails;
                    cout << "\nEnter book details." << endl;
                    cout << "ISBN: ";
                    cin.ignore();
                    getline(cin, bookDetails);
                    bookDetails = number_clear_formatting(bookDetails);
                    if (is_number(bookDetails)) {
                        if (filesystem::exists("./data/" + bookDetails + ".txt")) { //if txt file of the same ISBN exist in database
                            cout << "Book already existed." << endl;
                            string select;
                            cout << "Override previous entry?[Y/N]: ";
                            cin >> select;
                            select = toUpperCase(select);
                            if (select == "Y" || select == "YES") {
                                if (filesystem::remove("./data/" + bookDetails + ".txt"))
                                    cout << "Insert new details." << endl;
                            }
                            else if (select == "N" || select == "NO") {
                                cout << "Book not inserted." << endl;
                                break;
                            }
                            else {
                                cout << "Not a valid input. Try again." << endl;
                                break;
                            }
                            cin.ignore();
                        }
                        book newBook;
                        newBook.ISBN = bookDetails;

                        cout << "Title: ";
                        getline(cin, bookDetails);
                        newBook.title = bookDetails;

                        cout << "Author: ";
                        getline(cin, bookDetails);
                        newBook.author = bookDetails;

                        cout << "Genre: ";
                        getline(cin, bookDetails);
                        newBook.genre = bookDetails;

                        cout << "Publisher: ";
                        getline(cin, bookDetails);
                        newBook.publisher = bookDetails;

                        newBook.status = "Available";

                        newBook.addToDatabase();

                        if (filesystem::exists("./data/" + newBook.ISBN + ".txt")) {
                            cout << "Book successfully inserted." << endl;
                        }
                    }
                    else {
                        cout << "Not a valid ISBN number." << endl;
                    }
                }
                    break;
                case 2:
                    break;
                case 3: {
                    string toDelete;
                    cout << "\nInput ISBN number: ";
                    cin.ignore();
                    getline(cin, toDelete);

                    if (!toDelete.empty()) {
                        toDelete = number_clear_formatting(toDelete);
                        if (is_number(toDelete)) {
                            book BookData = getDataList(toDelete);

                            if (!BookData.title.empty()) {
                                BookData.deleteBook();
                                if (!filesystem::exists("./data/" + toDelete + ".txt"))
                                    cout << "Book successfully deleted." << endl;
                                else
                                    cout << "Book failed to delete." << endl;
                            }
                            else cout << "Book doesn't exist in our database." << endl;
                        }
                        else cout << "Not a valid ISBN number." << endl;
                    }
                }
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                default:
                    break;
                }
            }
        }
            break;
        case 7:
            return 0;
            break;
        default:
            cout << "Invalid input!" << endl;
        }

    }

}

void printBookData(const book& Book) {
    cout << "ISBN: " << Book.ISBN << endl;
    cout << "Title: " << Book.title << endl;
    cout << "Author: " << Book.author << endl;
    cout << "Genre: " << Book.genre << endl;
    cout << "Publisher: " << Book.publisher << endl;
    cout << "Status: " << Book.status << endl;
    cout << "Borrower Record: " << endl;
    if (!Book.borrower_record.empty()) {
        for (string borrower : Book.borrower_record) {
            cout << borrower << endl;
        }
    }
}

string number_clear_formatting(const string& text) {
    string returnString;
    for (char letter : text) {
        if (letter != '-' && letter != ' ') {
            returnString += letter;
        }
    }
    return returnString;
}

bool is_number(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}