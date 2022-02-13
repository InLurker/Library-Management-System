#pragma once
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <filesystem>

class book {
public:
    std::string ISBN;
    std::string title;
    std::string author;
    std::string genre;
    std::string publisher;
    std::string status;
    std::vector <std::string> borrower_record;
    void addToDatabase();
    void borrowBook(std::string name, std::string phoneNum);
    void reserveBook(std::string name, std::string phoneNum);
    void returnBook();
    void modifyBorrower(int rowIndex, std::string name, std::string phoneNum);
    void deleteBorrower(int rowIndex);
    void modifyDetails(std::string detailType, std::string newDetail);
    void deleteBook();
};

#endif