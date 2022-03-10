#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "IndexSearching.h"
#include "book_indexing.h"
#include "Data.h"
#include "Book.h"
#include "Password.h"

using namespace std;

void printBookData(const book &Book);
string number_clear_formatting(const string& text);
bool is_number(const string& str);
void clearScreen();
book searchBook();

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
        cout << "7. Change password" << endl;
        cout << "8. Exit" << endl;
        cout << "Select an action: ";
        cin >> action;

        switch (action) {
        case 1: {
            book BookData = searchBook();
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
                        cin.ignore();
                        cout << "Name: ";
                        getline(cin, name);
                        cout << "Phone No: ";
                        getline(cin, phoneNum);

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
                    string toCheck;
                    cin.ignore();
                    cout << "Enter password: ";
                    getline(cin, toCheck);
                    clearScreen();
                    if (checkPassword(toCheck)) {
                        BookData.deleteBook();
                        cout << "Book successfully deleted." << endl;
                    }
                    else cout << "Wrong password!" << endl;
                }
                else if (action != count + 2) {
                    clearScreen();
                    cout << "Not a valid input. Try again." << endl;
                }
                else clearScreen();
            }
        }
              break;
        case 2: {
            string toCheck;
            cin.ignore();
            cout << "Enter password: ";
            getline(cin, toCheck);
            clearScreen();
            if (checkPassword(toCheck)) {
                string bookDetails;
                cout << "Enter book details." << endl;
                cout << "ISBN: ";
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
            else cout << "Wrong password!" << endl;
        }
              break;
        case 3: {
            book BookData = searchBook();
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
            break;
        case 4: {
            book BookData = searchBook();
            if (BookData.status == "Available") {
                string name, phoneNum;
                cin.ignore();
                cout << "Name: ";
                getline(cin, name);
                cout << "Phone No: ";
                getline(cin, phoneNum);
                clearScreen();
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
            break;
        case 5: {
            book BookData = searchBook();
            if (BookData.title.empty())
                cout << "Book doesn't exist in the database." << endl;
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
                else if (BookData.status == "Reserved")
                    cout << "Book is already reserved." << endl;
                else cout << "Book is available to borrow." << endl;
            }
        }
            break;
        case 6: {
            string toCheck;
            cin.ignore();
            cout << "Enter password: ";
            getline(cin, toCheck);
            clearScreen();
            if (checkPassword(toCheck)) {
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
                    case 2: {
                        book BookData = searchBook();
                        if (!BookData.title.empty()) {
                            int selectionNum = 0;
                            cout << "Book Details:" << endl;
                            cout << ++selectionNum << ". " << "ISBN: " << BookData.ISBN << endl;
                            cout << ++selectionNum << ". " << "Title: " << BookData.title << endl;
                            cout << ++selectionNum << ". " << "Author: " << BookData.author << endl;
                            cout << ++selectionNum << ". " << "Genre: " << BookData.genre << endl;
                            cout << ++selectionNum << ". " << "Publisher: " << BookData.publisher << endl;

                            string options[5] = { "ISBN", "title", "author", "genre", "publisher" };
                            cout << "Select a detail to modify [1-5]: ";
                            cin >> selectionNum;
                            if (selectionNum > 0 && selectionNum < 6) {
                                string newDetail;
                                cin.ignore();
                                cout << "New " + options[selectionNum - 1] + ": ";
                                getline(cin, newDetail);
                                clearScreen();
                                if (selectionNum == 1) { //if user select ISBN
                                    if (filesystem::exists("./data/" + newDetail + ".txt")) {
                                        //if the ISBN overlap with another book
                                        cout << "ISBN number overlaps with an existing record." << endl;
                                        break;
                                    }
                                    else {
                                        newDetail = number_clear_formatting(newDetail);
                                        if (!is_number(newDetail)) {
                                            cout << "Not a valid ISBN number." << endl;
                                            break;
                                        }
                                    }
                                }
                                BookData.modifyDetails(options[selectionNum - 1], newDetail);
                                cout << "Book details successfully modified." << endl;
                            }
                            else {
                                clearScreen();
                                cout << "Not a valid input. Try again." << endl;
                            }
                        }
                        else cout << "Book doesn't exist in our database." << endl;
                    }
                          break;
                    case 3: {
                        book BookData = searchBook();
                        if (!BookData.title.empty()) {
                            BookData.deleteBook();
                            if (!filesystem::exists("./data/" + BookData.ISBN + ".txt")) //if data no longer exist
                                cout << "Book successfully deleted." << endl;
                            else
                                cout << "Book failed to delete." << endl;
                        }
                    }
                          break;
                    case 4: {
                        book BookData = searchBook();
                        if (!BookData.title.empty()) {
                            if (BookData.title.empty()) {
                                cout << "Book doesn't exist in our database." << endl;
                            }
                            else {
                                clearScreen();
                                int selectionNum = 0;
                                cout << "Borrower's Record:" << endl;
                                for (const string& borrower : BookData.borrower_record)
                                    cout << ++selectionNum << ". " << borrower << endl;
                                cout << endl;
                                if (selectionNum == 1) {
                                    string select;
                                    cout << "This book only has 1 borrower." << endl;
                                    cout << "Is this the borrower you'd like to modify? [Y/N]: ";
                                    cin >> select;
                                    select = toUpperCase(select);
                                    if (select == "N" || select == "NO") {
                                        clearScreen();
                                        cout << "Request cancelled." << endl;
                                        break;
                                    }
                                    else if (select != "Y" && select != "YES") {
                                        clearScreen();
                                        cout << "Not a valid input. Try again." << endl;
                                        break;
                                    }
                                }
                                else if (selectionNum > 1) {
                                    cout << "Select a borrower's record [1-" + to_string(selectionNum) + "]: ";
                                    cin >> selectionNum;
                                    if (selectionNum < 1 || selectionNum > BookData.borrower_record.size()) {
                                        clearScreen();
                                        cout << "Not a valid input. Try again." << endl;
                                        break;
                                    }
                                }
                                else if (selectionNum < 1) {
                                    clearScreen();
                                    cout << "No records available." << endl;
                                    break;
                                }
                                string name, phoneNum;
                                cin.ignore();
                                cout << "\nInsert new details." << endl;
                                cout << "Name: ";
                                getline(cin, name);
                                cout << "Phone No: ";
                                getline(cin, phoneNum);
                                clearScreen();
                                phoneNum = number_clear_formatting(phoneNum);

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
                        }
                    }
                          break;
                    case 5: {
                        book BookData = searchBook();
                        if (BookData.title.empty()) {
                            cout << "Book doesn't exist in our database." << endl;
                        }
                        else {
                            clearScreen();
                            int selectionNum = 0;
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
                                    BookData.deleteBorrower(selectionNum - 1);
                                    clearScreen();
                                    cout << "Borrower successfully deleted." << endl;
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
                                    BookData.deleteBorrower(selectionNum - 1);
                                    clearScreen();
                                    cout << "Borrower successfully deleted." << endl;
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
                          break;
                    case 6: {
                        book BookData = searchBook();
                        if (!BookData.title.empty()) {
                            int i = 0;
                            if (!BookData.borrower_record.empty()) {
                                cout << BookData.title << "'s borrower record:" << endl;
                                for (string& borrower : BookData.borrower_record)
                                    cout << ++i << ". " << borrower << endl;
                                cout << endl;
                            }
                            else cout << BookData.title << "'s borrower record is empty." << endl;
                        }
                    }
                        break;
                    case 7:
                        break;
                    default:
                        clearScreen();
                        cout << "Invalid input!" << endl;
                        break;
                    }
                }
            }
            else cout << "Wrong password!" << endl;
        }
            break;
        case 7: {
            string password;
            cin.ignore();
            cout << "Current password: ";
            getline(cin, password);
            clearScreen();
            if (checkPassword(password)) {
                cout << "Enter new password: ";
                getline(cin, password);
                savePassword(password);
                clearScreen();
                cout << "Password successfully saved." << endl;
            }
            else cout << "Wrong password!" << endl;
        }
            break;
        case 8:
            return 0;
            break;
        default:
            clearScreen();
            cout << "Invalid input!" << endl;
            break;
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

bool is_number(const string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

book searchBook() {
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
                        return getDataList(book_selection->ISBN);
                    }
                    else if (select == "N" || select == "NO")
                        cout << "Book title not selected." << endl;
                    else cout << "Not a valid input. Try again." << endl;
                }
                else if (selectionNum > 1) {
                    int select = 0;

                    cout << "Select an entry [1-" + to_string(selectionNum) + "]: ";
                    cin >> select;

                    clearScreen();
                    if (select > 0 && select <= selectionNum) {
                        book_indexing* book_selection = &searchResult.at(select - 1);
                        return getDataList(book_selection->ISBN);
                    }
                    else cout << "Not a valid input. Try again." << endl;
                }
            }
            else cout << "Book title not found." << endl;
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

                for (string author : searchResult)
                    cout << ++selectionNum << ". " << author << endl;

                string author;
                if (selectionNum == 1) { //when only 1 title matches query
                    string select;

                    cout << "\nOnly 1 author matches your query." << endl;
                    cout << "Is this the author you're looking for? [Y/N]: ";
                    cin >> select;

                    clearScreen();
                    select = toUpperCase(select);
                    if (select == "Y" || select == "YES")
                        author = searchResult.at(0);
                    else if (select == "N" || select == "NO")
                        cout << "Author not selected." << endl;
                    else cout << "Not a valid input. Try again." << endl;
                }
                else if (selectionNum > 1) {
                    int select = 0;

                    cout << "Select an entry [1-" + to_string(selectionNum) + "]: ";
                    cin >> select;

                    clearScreen();
                    if (select > 0 && select <= selectionNum)
                        author = searchResult.at(select - 1);
                    else cout << "Not a valid input. Try again." << endl;
                }

                if (!author.empty()) {
                    int selectionNum = 0;

                    clearScreen();
                    cout << author << "'s books:" << endl;
                    vector <book_indexing> authorBooks = getBookList("author", author);

                    for (book_indexing& book : authorBooks)
                        cout << ++selectionNum << ". " << book.title << endl;

                    if (selectionNum == 1) { //when author only has 1 book
                        string select;

                        cout << '\n' << author << " only has 1 book." << endl;
                        cout << "Is this the book you're looking for? [Y/N]: ";
                        cin >> select;

                        clearScreen();
                        select = toUpperCase(select);
                        if (select == "Y" || select == "YES") {
                            book_indexing* book_selection = &authorBooks.at(0);
                            return getDataList(book_selection->ISBN);
                        }
                        else if (select == "N" || select == "NO")
                            cout << "Book title not selected." << endl;
                        else
                            cout << "Not a valid input. Try again." << endl;
                    }
                    else if (selectionNum > 1) {
                        int select = 0;

                        cout << "Select an entry [1-" + to_string(selectionNum) + "]: ";
                        cin >> select;

                        clearScreen();
                        if (select > 0 && select <= selectionNum) {
                            book_indexing* book_selection = &authorBooks.at(select - 1);
                            return getDataList(book_selection->ISBN);
                        }
                        else cout << "Not a valid input. Try again." << endl;
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
                    if (select == "Y" || select == "YES")
                        genre = genreList.at(0);
                    else if (select == "N" || select == "NO")
                        cout << "Genre not selected." << endl;
                    else
                        cout << "Not a valid input. Try again." << endl;
                }
                else if (genreList.size() > 1) {
                    int select = 0;
                    cout << "Select a genre [1-" + to_string(selectionNum) + "]: ";
                    cin >> select;
                    clearScreen();
                    if (select > 0 && select <= selectionNum)
                        genre = genreList.at(select - 1);
                    else
                        cout << "Not a valid input. Try again." << endl;
                }

                if (!genre.empty()) {
                    clearScreen();
                    int selectionNum = 0;

                    cout << "Books under " << '\"' << genre << '\"' << " genre:" << endl;
                    vector <book_indexing> genreBooks = getBookList("genre", genre);

                    for (book_indexing& book : genreBooks)
                        cout << ++selectionNum << ". " << book.title << endl;

                    if (selectionNum == 1) { //when author only has 1 book
                        string select;

                        cout << '\n' << "Genre \"" << genre << "\" only has 1 book." << endl;
                        cout << "Is this the book you're looking for? [Y/N]: ";
                        cin >> select;
                        clearScreen();
                        select = toUpperCase(select);
                        if (select == "Y" || select == "YES") {
                            book_indexing* book_selection = &genreBooks.at(0);
                            return getDataList(book_selection->ISBN);
                        }
                        else if (select == "N" || select == "NO")
                            cout << "Book title not selected." << endl;
                        else
                            cout << "Not a valid input. Try again." << endl;
                    }
                    else if (selectionNum > 1) {
                        int select = 0;

                        cout << "Select an entry [1-" + to_string(selectionNum) + "]: ";
                        cin >> select;
                        clearScreen();
                        if (select > 0 && select <= selectionNum) {
                            book_indexing* book_selection = &genreBooks.at(select - 1);
                            return getDataList(book_selection->ISBN);
                        }
                        else cout << "Not a valid input. Try again." << endl;
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
                for (string publisher : searchResult)
                    cout << ++selectionNum << ". " << publisher << endl;
                string publisher;
                if (selectionNum == 1) {
                    string select;
                    cout << "\nOnly 1 publisher matches your query." << endl;
                    cout << "Is this the publisher you're looking for? [Y/N]: ";
                    cin >> select;
                    select = toUpperCase(select);
                    clearScreen();
                    if (select == "Y" || select == "YES")
                        publisher = searchResult.at(0);
                    else if (select == "N" || select == "NO")
                        cout << "Publisher not selected." << endl;
                    else
                        cout << "Not a valid input. Try again." << endl;
                }
                else if (selectionNum > 1) {
                    int select = 0;
                    cout << "Select an entry [1-" + to_string(selectionNum) + "]: ";
                    cin >> select;
                    clearScreen();
                    if (select > 0 && select <= selectionNum)
                        publisher = searchResult.at(select - 1);
                    else
                        cout << "Not a valid input. Try again." << endl;
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
                            return getDataList(book_selection->ISBN);
                        }
                        else if (select == "N" || select == "NO")
                            cout << "Book title not selected." << endl;
                        else
                            cout << "Not a valid input. Try again." << endl;
                    }
                    else if (selectionNum > 1) {
                        int select = 0;

                        cout << "Select an entry [1-" + to_string(selectionNum) + "]: ";
                        cin >> select;

                        clearScreen();
                        if (select > 0 && select <= selectionNum) {
                            book_indexing* book_selection = &publisherBooks.at(select - 1);
                            return getDataList(book_selection->ISBN);
                        }
                        else {
                            cout << "Not a valid input. Try again." << endl;
                        }
                    }
                }
            }
            else cout << "Publisher not found." << endl;
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
                    if (filesystem::exists("./data/" + search_query + ".txt"))
                        return getDataList(search_query);
                    else cout << "Book doesn't exist in our database." << endl;
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
    }
    //if reach this state, return empty object
    book emptyBook;
    return emptyBook;
}