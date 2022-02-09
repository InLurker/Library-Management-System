#pragma once
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

class book {
public:
    std::string ISBN;
    std::string title;
    std::string author;
    std::string genre;
    std::string publisher;
    std::string status;
    std::vector <std::string> borrower_record;
    void updateData();
};

#endif