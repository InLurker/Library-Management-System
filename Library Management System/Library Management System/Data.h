#pragma once
#ifndef DATA_H
#define DATA_H
#include<vector>
#include<string>
#include<filesystem>
#include<fstream>
#include"book_indexing.h"
using namespace std;
vector<string>searchDataFiles(string query);
vector <book_indexing> getDataList(string filename);
#endif