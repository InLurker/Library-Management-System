#pragma once
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "book_indexing.h"

class book {
public:
    std::string ISBN;
    std::string title;
    std::string author;
    std::string genre;
    std::string publisher;
    std::string status;
    std::vector <std::string> borrower_record;
    std::string reserveName;
    void addToDatabase(); //adds book record to database and its instances into index_files
    void borrowBook(const std::string& name, const std::string& phoneNum); //receives string arg for name and phoneNum to add to borrower record
    void reserveBook(const std::string& name, const std::string& phoneNum); //receives string arg for name and phoneNum to assign to reserveName
    void returnBook(); //manages book status when being returned back to the library
    void modifyBorrower(int rowIndex, const std::string& name, const std::string& phoneNum); //modify a certain borrwer's info with new arguments
    void deleteBorrower(int rowIndex); //remove a certain borrower from the records
    void modifyDetails(const std::string& detailType, const std::string& newDetail); //make a modification to book's data
    void deleteBook(); //removes book from database and index_files
private:
    void updateDetails(); //updates book's details in "data" directory
    int binarySearchPosition(const std::vector<book_indexing>& vectorArray, const book_indexing* item) const; //returns an index position of book for insertion or removal
};

#endif