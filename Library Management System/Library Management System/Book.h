#pragma once
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

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
    void addToDatabase();
    void borrowBook(const std::string& name, const std::string& phoneNum);
    void reserveBook(const std::string& name, const std::string& phoneNum);
    void returnBook();
    void modifyBorrower(int rowIndex, const std::string& name, const std::string& phoneNum);
    void deleteBorrower(int rowIndex);
    void modifyDetails(const std::string& detailType, const std::string& newDetail);
    void deleteBook(); 
private:
    void updateDetails();
};
#endif
