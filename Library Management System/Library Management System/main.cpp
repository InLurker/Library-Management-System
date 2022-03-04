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

void modifyInfo(const string& name, const string& phoneNum, const string& search_query, int selectionNum);
void deleteBorrower(const string& search_query, int selectionNum);
void printBookData(const book &Book);
string number_clear_formatting(const string& text);
bool is_number(const string& str);
void clearScreen();

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
    cout << endl;

    bool loop = true;

    while (loop) {
        int action;

        cout << "What can we help you with?" << endl;
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
            clearScreen();
            while (option != 6) {
                cout << "Search book by:" << endl;
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

                    clearScreen();
                    if (!searchResult.empty()) {
                        cout << "Search result for \"" + search_query + "\": " << endl;

                        for (book_indexing& book : searchResult) //output search result
                            cout << ++selectionNum << ". " << book.title << endl;

                        if (selectionNum == 1) { //when only 1 title matches query
                            string select;

                            cout << "\nOnly 1 title matches your query." << endl;
                            cout << "Is this the book you're looking for? [Y/N]: ";
                            cin >> select;

                            clearScreen();
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

                            clearScreen();
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
                    clearScreen();

                    if (!searchResult.empty()) {
                        cout << "Search result for \"" + search_query + "\": " << endl;

                        for (string author : searchResult) {
                            cout << ++selectionNum << ". " << author << endl;
                        }
                        string author;
                        if (selectionNum == 1) { //when only 1 title matches query
                            string select;

                            cout << "\nOnly 1 author matches your query." << endl;
                            cout << "Is this the author you're looking for? [Y/N]: ";
                            cin >> select;

                            clearScreen();
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

                            clearScreen();
                            if (select > 0 && select <= selectionNum) {
                                author = searchResult.at(select - 1);
                            }
                            else {
                                cout << "Not a valid input. Try again." << endl;
                            }
                        }


                        if (!author.empty()) {
                            int selectionNum = 0;

                            clearScreen();
                            cout << author << "'s books:" << endl;
                            vector <book_indexing> authorBooks = getBookList("author", author);

                            for (book_indexing& book : authorBooks) {
                                cout << ++selectionNum << ". " << book.title << endl;
                            }

                            if (selectionNum == 1) { //when author only has 1 book
                                string select;

                                cout << '\n' << author << " only has 1 book." << endl;
                                cout << "Is this the book you're looking for? [Y/N]: ";
                                cin >> select;

                                clearScreen();
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

                                clearScreen();
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

                    clearScreen();
                    if (!genreList.empty()) {
                        cout << "List of available genres: " << endl;
                        for (string genreEntries : genreList) {
                            cout << ++selectionNum << ". " << genreEntries << endl;
                        }

                        if (genreList.size() == 1) { //when only 1 title matches query
                            string select;

                            cout << "\nOnly 1 genre available." << endl;
                            cout << "Is this the genre you're looking for? [Y/N]: ";
                            cin >> select;
                            clearScreen();
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
                            int select = 0;
                            cout << "Select a genre [1-" + to_string(selectionNum) + "]: ";
                            cin >> select;
                            clearScreen();
                            if (select > 0 && select <= selectionNum) {
                                genre = genreList.at(select - 1);
                            }
                            else {
                                cout << "Not a valid input. Try again." << endl;
                            }
                        }

                        if (!genre.empty()) {
                            clearScreen();
                            int selectionNum = 0;

                            cout << "Books under " << '\"' << genre << '\"' << " genre:" << endl;
                            vector <book_indexing> genreBooks = getBookList("genre", genre);

                            for (book_indexing& book : genreBooks) {
                                cout << ++selectionNum << ". " << book.title << endl;
                            }

                            if (selectionNum == 1) { //when author only has 1 book
                                string select;

                                cout << '\n' << "Genre \"" << genre << "\" only has 1 book." << endl;
                                cout << "Is this the book you're looking for? [Y/N]: ";
                                cin >> select;
                                clearScreen();
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
                                clearScreen();
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
                    clearScreen();
                    if (!searchResult.empty()) {
                        cout << "Search result for \"" + search_query + "\": " << endl;
                        for (string publisher : searchResult) {
                            cout << ++selectionNum << ". " << publisher << endl;
                        }
                        string publisher;
                        if (selectionNum == 1) {
                            string select;
                            cout << "\nOnly 1 publisher matches your query." << endl;
                            cout << "Is this the publisher you're looking for? [Y/N]: ";
                            cin >> select;
                            select = toUpperCase(select);
                            clearScreen();
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
                            clearScreen();
                            if (select > 0 && select <= selectionNum) {
                                publisher = searchResult.at(select - 1);
                            }
                            else {
                                cout << "Not a valid input. Try again." << endl;
                            }
                        }
                        if (!publisher.empty()) {
                            clearScreen();
                            int selectionNum = 0;
                            cout << publisher << "'s books:" << endl;
                            vector <book_indexing> publisherBooks = getBookList("publisher", publisher);
                            for (book_indexing& book : publisherBooks) {
                                cout << ++selectionNum << ". " << book.title << endl;
                            }
                            if (selectionNum == 1) {
                                string select;
                                cout << '\n' << "Only 1 book published by " << publisher << "." << endl;
                                cout << "Is this the book you're looking for? [Y/N]: ";
                                cin >> select;

                                clearScreen();
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

                                clearScreen();
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
                    clearScreen();
                    if (!search_query.empty()) {
                        search_query = number_clear_formatting(search_query);
                        if (is_number(search_query)) {
                            BookData = getDataList(search_query);
                            if (BookData.title.empty()) {
                                cout << "Book doesn't exist in our database." << endl;
                            } else clearScreen();
                        }
                        else cout << "Not a valid ISBN number." << endl;
                    }
                }
                      break;
                case 6:
                    clearScreen();
                    break;
                default:
                    clearScreen();
                    cout << "Invalid input!" << endl;
                }

                if (!BookData.title.empty()) {
                    printBookData(BookData);

                    int count;
                    void (book:: * function_ptr) (const string&, const string&) = NULL;

                    cout << "\nActions to perform:" << endl;

                    if (BookData.status == "Available") {
                        function_ptr = &book::borrowBook;
                        cout << "1. Borrow book" << endl;
                        count = 1;
                    }
                    else if (BookData.status == "Borrowed") {
                        function_ptr = &book::reserveBook;
                        cout << "1. Reserve book" << endl;
                        cout << "2. Return book" << endl;
                        count = 2;
                    }
                    else {
                        cout << "1. Return book" << endl;
                        count = 1;
                    }
                    cout << count + 1 << ". Delete book" << endl;
                    cout << count + 2 << ". Cancel" << endl;
                    cout << "Select an action: ";

                    cin >> action;

                    if (action == 1) {
                        if (function_ptr != NULL) {
                            string name, phoneNum;
                            cout << "Name: ";
                            cin >> name;
                            cout << "Phone No: ";
                            cin >> phoneNum;

                            clearScreen();
                            phoneNum = number_clear_formatting(phoneNum);
                            if (is_number(phoneNum)) {
                                (BookData.*function_ptr)(name, phoneNum);
                                if (count == 1)
                                    cout << "Book successfully borrowed." << endl;
                                else {
                                    cout << "Book successfully reserved." << endl;
                                }
                            }
                            else cout << "Invalid phone number." << endl;
                        }
                        else {
                            BookData.returnBook();
                            clearScreen();
                            cout << "Book successfully returned." << endl;
                        }
                    }
                    else if (action == 2 && count == 2) {
                        BookData.returnBook();
                        clearScreen();
                        cout << "Book successfully returned." << endl;
                    }
                    else if (action == count + 1) {
                        //Password verification to be implemented
                        BookData.deleteBook();
                        clearScreen();
                        cout << "Book successfully deleted." << endl;
                    }
                    else if (action != count + 2) {
                        clearScreen();
                        cout << "Not a valid input. Try again." << endl;
                    }
                    else clearScreen();
                }
            }
        }
            break;
        case 2: {
            string bookDetails;
            clearScreen();
            cout << "Enter book details." << endl;
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
                    clearScreen();
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

                clearScreen();
                if (filesystem::exists("./data/" + newBook.ISBN + ".txt")) {
                    cout << "Book successfully inserted." << endl;
                }
            }
            else {
                clearScreen();
                cout << "Not a valid ISBN number." << endl;
            }
        }
            break;
        case 3: {
            clearScreen();
            string search_query;
            string bookDetails;
            book BookData;
            cout << "ISBN: ";
            cin.ignore();
            getline(cin, search_query);
            clearScreen();
            if (!search_query.empty()) {
                search_query = number_clear_formatting(search_query);
                if (is_number(search_query)) {
                    BookData = getDataList(search_query);
                    if (BookData.title.empty()) {
                        cout << "Book doesn't exist in the database." << endl;
                    }
                    else {
                        if (BookData.status != "Available") {
                            BookData.returnBook();
                            cout << "Book successfully returned." << endl;
                        }
                        else {
                            cout << "Book is not Borrowed." << endl;
                        }
                    }
                }
                else cout << "Not a valid ISBN number." << endl;
            }
        }
            break;
        case 4: {
            clearScreen();
            string searchKey;
            string bookDetails;
            book BookData;
            cout << "ISBN: ";
            cin.ignore();
            getline(cin, searchKey);
            clearScreen();
            if (!searchKey.empty()) {
                searchKey = number_clear_formatting(searchKey);
                if (is_number(searchKey)) {
                    BookData = getDataList(searchKey);
                    if (BookData.title.empty()) {
                        cout << "Book doesn't exist in the database." << endl;
                    }
                    else {
                        if(BookData.status == "Available") {
                            string name, phoneNum;
                            cout << "Name: ";
                            getline(cin, name);
                            cout << "Phone No: ";
                            getline(cin, phoneNum);

                            phoneNum = number_clear_formatting(phoneNum);
                            if (is_number(phoneNum)) {
                                BookData.borrowBook(name, phoneNum);
                                cout << "Book successfully borrowed." << endl;
                            }
                            else cout << "Invalid phone number." << endl;
                        }
                        else {
                            cout << "Book is not available." << endl;
                        }
                    }
                }
                else cout << "Not a valid ISBN number." << endl;
            }

        }
            break;
        case 5: {
            clearScreen();
            string searchKey;
            string bookDetails;
            book BookData;
            cout << "ISBN: ";
            cin.ignore();
            getline(cin, searchKey);
            clearScreen();
            if (!searchKey.empty()) {
                searchKey = number_clear_formatting(searchKey);
                if (is_number(searchKey)) {
                    BookData = getDataList(searchKey);
                    if (BookData.title.empty()) {
                        cout << "Book doesn't exist in the database." << endl;
                    }
                    else {
                        if (BookData.status == "Borrowed") {
                            string name, phoneNum;
                            cout << "Name: ";
                            getline(cin, name);
                            cout << "Phone No: ";
                            getline(cin, phoneNum);

                            phoneNum = number_clear_formatting(phoneNum);
                            if (is_number(phoneNum)) {
                                BookData.reserveBook(name, phoneNum);
                                cout << "Book successfully reserved." << endl;
                            }
                            else cout << "Invalid phone number." << endl;
                        }
                        else if (BookData.status == "Reserved") {
                            cout << "Book is already reserved." << endl;
                        }
                        else cout << "Book is available to borrow." << endl;
                    }
                }
                else cout << "Not a valid ISBN number." << endl;
            }
        }
            break;
        case 6: {
            int option = 0;
            clearScreen();
            while (option != 7) {
                cout << "Administrator Mode:" << endl;
                cout << "1. Insert a book" << endl;
                cout << "2. Modify a book" << endl;
                cout << "3. Delete a book" << endl;
                cout << "4. Modify a borrower" << endl;
                cout << "5. Delete a borrower" << endl;
                cout << "6. Search a borrowing list" << endl;
                cout << "7. Exit Administrator Mode" << endl;
                cout << "Select an option: ";
                cin >> option;

                clearScreen();
                switch (option) {
                case 1: {
                    string bookDetails;
                    cout << "Enter book details." << endl;
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
                            clearScreen();
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

                        clearScreen();
                        if (filesystem::exists("./data/" + newBook.ISBN + ".txt")) {
                            cout << "Book successfully inserted." << endl;
                        }
                    }
                    else {
                        clearScreen();
                        cout << "Not a valid ISBN number." << endl;
                    }
                }
                    break;
                case 2:
                    break;
                case 3: {
                    string toDelete;
                    cout << "Input ISBN number: ";
                    cin.ignore();
                    getline(cin, toDelete);
                    clearScreen();
                    if (!toDelete.empty()) {
                        toDelete = number_clear_formatting(toDelete);
                        if (is_number(toDelete)) {
                            book BookData = getDataList(toDelete);

                            clearScreen();
                            if (!BookData.title.empty()) {
                                BookData.deleteBook();
                                if (!filesystem::exists("./data/" + toDelete + ".txt")) //if data no longer exist
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
                case 4: {
                    string search_query, name, phoneNum;
                    book BookData;
                    int selectionNum = 0;
                    cout << "Input ISBN number: ";
                    cin.ignore();
                    getline(cin, search_query);
                    clearScreen();
                    if (!search_query.empty()) {
                        search_query = number_clear_formatting(search_query);
                        if (is_number(search_query)) {
                            BookData = getDataList(search_query);
                            if (BookData.title.empty()) {
                                cout << "Book doesn't exist in our database." << endl;
                            }
                            else {
                                clearScreen();
                                for (const string& borrower : BookData.borrower_record) {
                                    cout << ++selectionNum << ". " << borrower << endl;
                                }
                                cout << endl;
                                if (selectionNum == 1) {
                                    string select;
                                    cout << "This book only has 1 borrower." << endl;
                                    cout << "Is this the borrower you'd like to modify? [Y/N]: ";
                                    cin >> select;
                                    select = toUpperCase(select);
                                    if (select == "Y" || select == "YES") {
                                        cout << "Name: ";
                                        cin.ignore();
                                        getline(cin, name);
                                        cout << "Phone No: ";
                                        getline(cin, phoneNum);
                                        clearScreen();
                                        phoneNum = number_clear_formatting(phoneNum);
                                        modifyInfo(name, phoneNum, search_query, selectionNum);
                                    }
                                    else if (select == "N" || select == "NO") {
                                        clearScreen();
                                        cout << "Request cancelled." << endl;
                                    }
                                    
                                }
                                else if (selectionNum > 1) {
                                    cout << "Select a borrower's record [1-" + to_string(selectionNum) + "]: ";
                                    cin >> selectionNum;
                                    if (selectionNum > 0 && selectionNum <= BookData.borrower_record.size()) {
                                        cin.ignore();
                                        cout << "Name: ";
                                        getline(cin, name);
                                        cout << "Phone No: ";
                                        getline(cin, phoneNum);
                                        clearScreen();
                                        phoneNum = number_clear_formatting(phoneNum);
                                        modifyInfo(name, phoneNum, search_query, selectionNum);
                                    }
                                    else {
                                        clearScreen();
                                        cout << "Not a valid input. Try again." << endl;
                                    }
                                }
                                else if (selectionNum < 1) {
                                    clearScreen();
                                    cout << "No records available." << endl;
                                }
                            }
                        }
                        else cout << "Not a valid ISBN number." << endl;
                    }
                }
                      break;
                case 5: {
                    string search_query, name, phoneNum;
                    book BookData;
                    int selectionNum = 0;
                    cout << "Input ISBN number: ";
                    cin.ignore();
                    getline(cin, search_query);
                    clearScreen();
                    if (!search_query.empty()) {
                        search_query = number_clear_formatting(search_query);
                        if (!search_query.empty()) {
                            search_query = number_clear_formatting(search_query);
                            if (is_number(search_query)) {
                                BookData = getDataList(search_query);
                                if (BookData.title.empty()) {
                                    cout << "Book doesn't exist in our database." << endl;
                                }
                                else {
                                    clearScreen();
                                    for (const string& borrower : BookData.borrower_record) {
                                        cout << ++selectionNum << ". " << borrower << endl;
                                    }
                                    cout << endl;
                                    if (selectionNum == 1) {
                                        string select;
                                        cout << "This book only has 1 borrower." << endl;
                                        cout << "Is this the borrower you'd like to delete? [Y/N]? ";
                                        cin >> select;
                                        select = toUpperCase(select);
                                        if (select == "Y" || select == "YES") {
                                            deleteBorrower(search_query, selectionNum);
                                        }
                                        else if (select == "N" || select == "NO") {
                                            clearScreen();
                                            cout << "Borrower not deleted." << endl;
                                        }
                                        else {
                                            clearScreen();
                                            cout << "Not a valid input. Try again." << endl;
                                        }
                                    }
                                    if (selectionNum > 1) {
                                        cout << "Select a borrower's record [1-" + to_string(selectionNum) + "]: ";
                                        cin >> selectionNum;
                                        if (selectionNum > 0 && selectionNum <= BookData.borrower_record.size()) {
                                            deleteBorrower(search_query, selectionNum);
                                        }
                                        else {
                                            clearScreen();
                                            cout << "Not a valid input. Try again." << endl;
                                        }
                                    }
                                    else if (selectionNum < 1) {
                                        clearScreen();
                                        cout << "No records available." << endl;
                                    }
                                }
                            }
                            else cout << "Not a valid ISBN number." << endl;
                        }
                    }
                }
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
            clearScreen();
            cout << "Invalid input!" << endl;
        }
    }

}

void deleteBorrower(const string& search_query, int selectionNum) {
    book BookData;
    BookData = getDataList(search_query);
    BookData.deleteBorrower(selectionNum - 1);
    clearScreen();
    cout << "Borrower successfully deleted." << endl;
}

void modifyInfo(const string& name, const string& phoneNum, const string& search_query, int selectionNum) {
    book BookData;
    BookData = getDataList(search_query);
    if (is_number(phoneNum)) {
        BookData.modifyBorrower(selectionNum - 1, name, phoneNum);
        clearScreen();
        cout << "Borrower successfully modified." << endl;
    }
    else {
        clearScreen();
        cout << "Invalid phone number." << endl;
    }
}

void printBookData(const book& Book) {
    cout << "ISBN: " << Book.ISBN << endl;
    cout << "Title: " << Book.title << endl;
    cout << "Author: " << Book.author << endl;
    cout << "Genre: " << Book.genre << endl;
    cout << "Publisher: " << Book.publisher << endl;
    cout << "Status: " << Book.status << endl;

    if (!Book.borrower_record.empty()) {
        cout << "\nBorrower Record: " << endl;
        if (!Book.borrower_record.empty()) {
            for (const string& borrower : Book.borrower_record) {
                cout << borrower << endl;
            }
        }
    }
}

string number_clear_formatting(const string& text) {
    string returnString;
    for (const char &letter : text) {
        if (letter != '-' && letter != ' ' && letter != '+' && letter != '(' && letter != ')') {
            returnString += letter;
        }
    }
    return returnString;
}

bool is_number(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}
