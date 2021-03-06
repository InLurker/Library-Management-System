#pragma once

#ifndef INDEXSEARCHING_H
#define INDEXSEARCHING_H

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "book_indexing.h"

std::vector <book_indexing> searchByTitle(std::string query); //search for a title in the alphabetical directory
std::vector <std::string> searchIndexFiles(const std::string& searchType, std::string query); //search for a txt index file
std::vector <std::string> getIndexFiles(const std::string& searchType); //get all txt filenames
std::vector <book_indexing> getBookList(const std::string& searchType, const std::string& filename); //get book list from a known index file

std::string toUpperCase(std::string text);

#endif 